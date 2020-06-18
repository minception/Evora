#include "minimax_ai.h"
#include "center_offer.h"
#include <memory>
#include "drop_center.h"
#include "factory_offer.h"
#include "drop_factory.h"
#include "utils.h"

int ai::minimax_ai::evaluate(std::shared_ptr<control::game_controller>& controller)
{
	int moves = controller->add_wall_tiling_phase();
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

bool ai::minimax_ai::update_scores(int player_index, int& best_score, int score, int& alpha, int& beta)
{
	if (player_index == m_board_index)
	{
		if (score > best_score)
		{
			best_score = score;
			if(score > alpha)
			{
				alpha = score;
			}
			return true;
		}
	}
	else
	{
		if (score < best_score)
		{
			best_score = score;
			if(score < beta)
			{
				beta = score;
			}
			return true;
		}
	}
	return false;
}

int ai::minimax_ai::minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller, int alpha, int beta)
{
	if(depth!= 0)
	{
		controller->step();
	}
	std::shared_ptr<model::game> game = controller->get_model();
	if(depth == m_max_depth && !game->round_finished())
	{
		m_round_finished = false;
	}
	if(depth == m_max_depth || game->round_finished())
	{
		return utils::evaluate(controller, m_board_index);
	}
	int best_score = player_index == m_board_index ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	int center_offers(0), factory_offers(0);
	std::vector<model::tile> center_colors = game->get_center_colors();
	// all center to pattern line moves
	for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
	{
		for (auto&& color : center_colors)
		{
			if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
			{
				auto&& move = std::make_unique<control::center_offer>(player_index, pattern_line_index, color);
				if (alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
				{
					return best_score;
				}
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
					auto&& move = std::make_unique<control::factory_offer>(factory_index, player_index, pattern_line_index, color);
					if (alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
					{
						return best_score;
					}
					factory_offers++;
				}
			}
		}
	}
	if (center_offers + factory_offers < 5)
	{
		// all factory to floor moves
		for (int factory_index = 0; factory_index < game->factory_count(); ++factory_index)
		{
			std::vector<model::tile> factory_colors = game->get_factory_colors(factory_index);
			for (auto&& color : factory_colors)
			{
				auto&& move = std::make_unique<control::drop_factory>(factory_index, player_index, color);
				if (alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
				{
					return best_score;
				}
			}
		}
		// all center to floor moves
		for (auto&& color : center_colors)
		{
			auto&& move = std::make_unique<control::drop_center>(player_index, color);
			if(alpha_beta_move(controller, std::move(move), best_score, depth, player_index, alpha, beta))
			{
				return best_score;
			}
		}
	}
	return best_score;
}

bool ai::minimax_ai::alpha_beta_move(const std::shared_ptr<control::game_controller>& controller, std::unique_ptr<control::command> move,
                                  int& best_score, int depth, int player_index, int& alpha, int& beta)
{
	int next_player = controller->get_current_player();
	controller->add_command(move->clone());
	int score = minimax(next_player, depth + 1, controller, alpha, beta);
	controller->player_move_back();
	bool updated = update_scores(player_index, best_score, score, alpha, beta);
	if (depth == 0 && updated)
	{
		m_best_move = std::move(move);
		return false;
	}
	if (alpha >= beta && updated)
	{
		return true;
	}
	return false;
}

void ai::minimax_ai::move()
{
	int max_move_score = std::numeric_limits<int>::min();
	m_max_depth = 0;
	m_end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(m_time);
	std::shared_ptr<control::game_controller> mockup = std::make_shared<control::game_controller>(*m_controller);
	m_round_finished = false;
	while(utils::time_left(m_end_time) && !m_round_finished)
	{
		m_round_finished = true;
		++m_max_depth;
		int alpha = std::numeric_limits<int>::min();
		int beta = std::numeric_limits<int>::max();
		minimax(m_board_index, 0, mockup, alpha, beta);
	}
	m_controller->add_command(std::move(m_best_move));
	m_controller->step();
}

const char* ai::minimax_ai::get_name() const
{
	return "MinimaxAI";
}
