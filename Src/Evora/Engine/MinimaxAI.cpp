#include "MinimaxAI.h"
#include "center_offer.h"
#include <memory>
#include "drop_center.h"
#include "factory_offer.h"
#include "drop_factory.h"

int AI::MinimaxAI::evaluate(std::shared_ptr<control::game_controller>& controller)
{
	int moves = controller->add_wall_tiling_faze();
	for (int i = 0; i < moves; ++i)
	{
		controller->step();
	}
	int score = 0;
	for (int player_index = 0; player_index < controller->get_model()->player_count(); ++player_index)
	{
		if(player_index == m_board_index)
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

int AI::MinimaxAI::minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller)
{
	controller->step();
	std::shared_ptr<model::game> game = controller->get_model();
	if(depth == m_max_depth || game->round_finished())
	{
		return evaluate(controller);
	}
	int next_player = (player_index + 1) % game->player_count();
	int best_score = player_index == m_board_index ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	std::unique_ptr<control::command> best_move;
	std::vector<model::tile> center_colors = game->get_center_colors();
	int center_offers = 0;
	int factory_offers = 0;
	// all center to pattern line moves
	for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
	{
		for (auto&& color : center_colors)
		{
			if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
			{
				//commands.push_back(std::move(std::make_unique<center_offer>(player_index, pattern_line_index, color)));
				controller->add_command(std::make_unique<control::center_offer>(player_index, pattern_line_index, color));
				int score = minimax(next_player, depth + 1, controller);
				if(player_index == m_board_index)
				{
					if(score > best_score)
					{
						best_score = score;
						if(depth == 0)
						{
							best_move = std::make_unique<control::center_offer>(player_index, pattern_line_index, color);
						}
					}
				}
				else
				{
					if(score < best_score)
					{
						best_score = score;
					}
				}
				controller->step_back();
				center_offers++;
			}
		}
	}
	for (int factory_index = 0; factory_index < game->factory_count(); ++factory_index)
	{
		std::vector<model::tile> factory_colors = game->get_factory_colors(factory_index);
		//all factory to pattern line moves
		for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
		{
			for (auto&& color : factory_colors)
			{
				if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
				{
					//commands.push_back(std::move(std::make_unique<factory_offer>(factory_index, player_index, pattern_line_index, color)));
					controller->add_command(std::make_unique<control::factory_offer>(factory_index, player_index, pattern_line_index, color));
					int score = minimax(next_player, depth + 1, controller);
					if (player_index == m_board_index)
					{
						if (score > best_score)
						{
							best_score = score;
							if (depth == 0)
							{
								best_move = std::make_unique<control::factory_offer>(factory_index, player_index, pattern_line_index, color);
							}
						}
					}
					else
					{
						if (score < best_score)
						{
							best_score = score;
						}
					}
					controller->step_back();
					factory_offers++;
				}
			}
		}
	}
	if (center_offers == 0 && factory_offers == 0)
	{
		// all factory to floor moves
		for (int factory_index = 0; factory_index < game->factory_count(); ++factory_index)
		{
			std::vector<model::tile> factory_colors = game->get_factory_colors(factory_index);
			for (auto&& color : factory_colors)
			{
				//commands.push_back(std::move(std::make_unique<drop_factory>(factory_index, player_index, color)));
				controller->add_command(std::make_unique<control::drop_factory>(factory_index, player_index, color));
				int score = minimax(next_player, depth + 1, controller);
				if (player_index == m_board_index)
				{
					if (score > best_score)
					{
						best_score = score;
						if (depth == 0)
						{
							best_move = std::make_unique<control::drop_factory>(factory_index, player_index, color);
						}
					}
				}
				else
				{
					if (score < best_score)
					{
						best_score = score;
					}
				}
				controller->step_back();
			}
		}
		// all center to floor moves
		for (auto&& color : center_colors)
		{
			//commands.push_back(std::move(std::make_unique<drop_center>(player_index, color)));
			controller->add_command(std::make_unique<control::drop_center>(player_index, color));
			int score = minimax(next_player, depth + 1, controller);
			if (player_index == m_board_index)
			{
				if (score > best_score)
				{
					best_score = score;
					if (depth == 0)
					{
						best_move = std::make_unique<control::drop_center>(player_index, color);
					}
				}
			}
			else
			{
				if (score < best_score)
				{
					best_score = score;
				}
			}
			controller->step_back();
		}
	}
	if(depth == 0)
	{
		m_controller->add_command(std::move(best_move));
		m_controller->step();
	}
	return best_score;
}

void AI::MinimaxAI::move()
{
	int max_move_score = std::numeric_limits<int>::min();
	int possible_moves = m_controller->possible_moves_count(m_board_index);
	printf("possible moves = %d\n", possible_moves);
	if (possible_moves > 80) m_max_depth = 4;
	else if (possible_moves > 40) m_max_depth = 3;
	else if (possible_moves > 20) m_max_depth = 4;
	else if (possible_moves > 10) m_max_depth = 5;
	else m_max_depth = 32;
	std::shared_ptr<control::game_controller> mockup = std::make_shared<control::game_controller>( *m_controller );
	minimax(m_board_index, 0, mockup);
}

const char* AI::MinimaxAI::get_name() const
{
	return "MinimaxAI";
}
