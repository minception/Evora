#include "scoring.h"

#include "center_offer.h"
#include "drop_center.h"
#include "drop_factory.h"
#include "factory_offer.h"
#include "game_controller.h"

namespace utils
{

	double score_move(std::shared_ptr<control::game_controller> controller, int factory_index, int player_index, int pattern_line_index, model::tile color)
	{
		if (pattern_line_index == model::COLORS) {
			return 0;
		}
		else {
			auto model = controller->get_model();
			int pattern_line_count = model->get_pattern_line_tile_count(player_index, pattern_line_index);
			int count;
			if (factory_index == model::COLORS) {
				count = model->center_tile_count(color);
			}
			else {
				count = model->factory_tile_count(factory_index, color);
			}
			int overflow = pattern_line_count + count - pattern_line_index - 1;
			overflow = overflow < 0 ? 0 : overflow;
			float fraction = (float)(pattern_line_count + count - overflow) / (pattern_line_index + 1);
			int penalty = model->get_floor_score(player_index, overflow);
			int score = controller->get_model()->get_wall_tile_score(player_index, pattern_line_index, color) * fraction;
			return score - penalty >= 0 ? score - penalty : 0;
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
					double score = score_move(controller, model::COLORS, player_index, pattern_line_index, color);
					auto&& move_score = std::make_pair(std::move(move), score);
					res.push_back(std::move(move_score));
				}
			}
			// all center to floor moves
			auto&& move = std::make_unique<control::drop_center>(player_index, color);
			double score = score_move(controller, model::COLORS, player_index, model::COLORS, color);
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
						double score = score_move(controller, factory_index, player_index, pattern_line_index, color);
						auto&& move_score = std::make_pair(std::move(move), score);
						res.push_back(std::move(move_score));
					}
				}
				// all factory to floor moves
				auto&& move = std::make_unique<control::drop_factory>(factory_index, player_index, color);
				double score = score_move(controller, factory_index, player_index, model::COLORS, color);
				auto&& move_score = std::make_pair(std::move(move), score);
				res.push_back(std::move(move_score));
			}
		}
		return res;
	}

	float evaluate_player(std::shared_ptr<control::game_controller>& controller, int player_index)
	{
		float score = controller->get_score(player_index);
		auto model = controller->get_model();
		bool last_round = false;
		for (int i = 0; i < model->player_count(); ++i)
		{
			for (size_t j = 0; j < model::COLORS; ++j)
			{
				model::wall wall = model->get_board(i).get_wall();
					if ((wall.line_count(j) == model::COLORS - 1 && model->pattern_line_full(i, j)) 
						|| wall.full_line(j)) {
						last_round = true;
						break;
					}
			}
		}
		// local copy of the wall
		model::wall wall = model->get_board(player_index).get_wall();
		for (size_t i = 0; i < model::COLORS; i++)
		{
			model::tile color = model->get_board(player_index).pattern_line_color(i);
			if (color == model::tile::empty) continue;
			int pl_count = model->get_pattern_line_tile_count(player_index, i);
			float frac = (float)pl_count / (i + 1);
			if (last_round) {
				frac = floorf(frac);
			}
			else {
				// frac = frac * frac;
				// 0.5 points for having a starter tile
				score += model->get_board(player_index).has_starter_tile() ? 0.5f : 0;
			}
			score += frac * wall.score_tile(i, color);
			wall.add_tile(i, color);
			score += wall.score_line(i);
		}
		for(size_t i = 0; i < model::COLORS; i++)
		{
			score += wall.score_row(i);
			score += wall.score_color((model::tile)i);
		}
		score += model->get_floor_score(player_index);
		return score;
	}

	float evaluate(std::shared_ptr<control::game_controller>& controller, int player_index) {
		float res = 0;
		for (size_t i = 0; i < controller->get_model()->player_count(); i++)
		{
			if (i == player_index) {
				res += evaluate_player(controller, i);
			}
			else {
				res -= evaluate_player(controller, i);
			}
		}
		return res;
	}
	int legacy_evaluate(std::shared_ptr<control::game_controller>& controller, int player_index) {
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

}
