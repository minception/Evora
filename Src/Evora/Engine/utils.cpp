#include "utils.h"
#include "center_offer.h"
#include "factory_offer.h"
#include "drop_factory.h"
#include "drop_center.h"

namespace utils
{
	int play_game(std::vector<std::unique_ptr<ai::ai>>& players, std::shared_ptr<control::game_controller> controller, int current_player)
	{
		int move_counter = 0;
		//bool round_over = false;
		while (true)
		{
			if (!controller->step())
			{
				if (controller->game_over())
				{
					return controller->get_winner();
				}
				//if (round_over)
				//{
				//	current_player = controller->get_first_player();
				//	round_over = false;
				//}
				current_player = controller->get_current_player();
				players[current_player]->move();
				++move_counter;
			}
			//else if (!round_over && controller->is_round_over())
			//{
			//	round_over = true;
			//}
		}
	}

	double score_move(std::shared_ptr<control::game_controller> controller, int player_index, int pattern_line_index, model::tile color)
	{
		if (pattern_line_index == model::COLORS) {
			return 0;
		}
		else {
			return controller->get_model()->score_wall_tile(player_index, pattern_line_index, color);
		}
	}

	std::vector<std::pair<std::unique_ptr<control::command>, double>> get_scored_moves(std::shared_ptr<control::game_controller> controller, int player_index)
	{
		std::vector<std::pair<std::unique_ptr<control::command>, double>> res;
		std::shared_ptr<model::game> game = controller->get_model();
		// tupples containing color of tiles and their amount respectively
		auto center_colors = game->get_center_colors();
		// all center to pattern line moves
		for (auto&& color : center_colors)
		{
			for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
			{
				if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
				{
					auto&& move = std::make_unique<control::center_offer>(player_index, pattern_line_index, color);
					double score = score_move(controller, player_index, pattern_line_index, color);
					auto&& move_score = std::make_pair(std::move(move), score);
					res.push_back(std::move(move_score));
				}
			}
			// all center to floor moves
			auto&& move = std::make_unique<control::drop_center>(player_index, color);
			double score = score_move(controller, player_index, model::COLORS, color);
			auto&& move_score = std::make_pair(std::move(move), score);
			res.push_back(std::move(move_score));
		}

		//all factory to pattern line moves
		for (int factory_index = 0; factory_index < game->factory_count(); ++factory_index)
		{
			auto factory_colors = game->get_factory_colors(factory_index);
			for (auto&& color : factory_colors)
			{
				for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
				{
					if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
					{
						auto&& move = std::make_unique<control::factory_offer>(factory_index, player_index, pattern_line_index, color);
						double score = score_move(controller, player_index, pattern_line_index, color);
						auto&& move_score = std::make_pair(std::move(move), score);
						res.push_back(std::move(move_score));
					}
				}
				// all factory to floor moves
				auto&& move = std::make_unique<control::drop_factory>(factory_index, player_index, color);
				double score = score_move(controller, player_index, model::COLORS, color);
				auto&& move_score = std::make_pair(std::move(move), score);
				res.push_back(std::move(move_score));
			}
		}
		return res;
	}

	int evaluate(std::shared_ptr<control::game_controller>& controller, int player_index)
	{
		int moves = controller->add_wall_tiling_phase();
		moves += controller->add_game_end();
		for (int i = 0; i < moves; ++i)
		{
			controller->step();
		}
		int score = 0;
		for (int player = 0; player < controller->get_model()->player_count(); ++player)
		{
			if (player == player_index)
			{
				score += controller->get_score(player_index);
			}
			else
			{
				score -= controller->get_score(player_index);
			}
		}
		for (int i = 0; i < moves; ++i)
		{
			controller->step_back();
		}
		return score;
	}

	bool time_left(std::chrono::system_clock::time_point end_time)
	{
		return std::chrono::system_clock::now() < end_time;
	}
}

