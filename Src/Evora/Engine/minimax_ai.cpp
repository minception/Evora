#include "minimax_ai.h"

#include <memory>

#include "center_offer.h"
#include "drop_factory.h"
#include "scoring.h"
#include "utils.h"


bool ai::minimax_ai::update_scores(int player_index, float& best_score, float score, float& alpha, float& beta)
{
	if (player_index == m_board_index)
	{
		if (score > best_score)
		{
			best_score = score;
			if (score > alpha)
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
			if (score < beta)
			{
				beta = score;
			}
			return true;
		}
	}
	return false;
}

float ai::minimax_ai::minimax(int player_index, int depth, std::shared_ptr<control::game_controller> controller, float alpha, float beta)
{
 	if (depth != 0)
	{
		controller->player_move();
	}
	std::shared_ptr<model::game> game = controller->get_model();
	if (depth == m_max_depth && !is_leaf(controller))
	{
		m_round_finished = false;
	}
	if (depth == m_max_depth || is_leaf(controller))
	{
		return utils::evaluate(controller, m_board_index);
	}
	float best_score = player_index == m_board_index ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max();
	auto scored_moves = utils::get_scored_moves(controller, player_index);
	std::sort(scored_moves.begin(), scored_moves.end(), [](auto&& a, auto&& b) {return std::get<1>(a) > std::get<1>(b); });
	for (auto&& move : scored_moves) {
		if (alpha_beta_move(controller, std::move(std::get<0>(move)), best_score, depth, player_index, alpha, beta))
		{
			return best_score;
		}
	}
	//if (depth == 0 && m_best_move == nullptr) {
	//	auto safenet_moves = utils::get_scored_moves(controller, player_index);
	//	std::sort(scored_moves.begin(), scored_moves.end(), [](auto&& a, auto&& b) {return std::get<1>(a) > std::get<1>(b); });
	//	m_best_move = std::move(std::get<0>(safenet_moves[0]));
	//}
	return best_score;
}

bool ai::minimax_ai::alpha_beta_move(const std::shared_ptr<control::game_controller>& controller, std::unique_ptr<control::command> move,
	float& best_score, int depth, int player_index, float& alpha, float& beta)
{
	int next_player = controller->get_current_player();
	controller->add_command(move->clone());
	float score = minimax(next_player, depth + 1, controller, alpha, beta);
	controller->player_move_back();
	bool updated = update_scores(player_index, best_score, score, alpha, beta);
	if (depth == 0 && updated)
	{
		m_best_move = std::move(move);
		return false;
	}
	if (m_abpruning && alpha >= beta && updated)
	{
		return true;
	}
	return false;
}

bool ai::minimax_ai::is_leaf(std::shared_ptr<control::game_controller>& controller)
{
	if(m_past_rounds)
	{
		return controller->game_over();
	}
	return controller->is_round_over();
}

void ai::minimax_ai::move()
{
	std::shared_ptr<control::game_controller> mockup = std::make_shared<control::game_controller>(*m_controller);
	if(m_fixed_depth)
	{

		float beta = std::numeric_limits<float>::max();
		float alpha = -beta;
		minimax(m_board_index, 0, mockup, alpha, beta);
	}
	else 
	{
		m_max_depth = 0;
		m_end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(m_time);
		m_round_finished = false;
		while (utils::time_left(m_end_time) && !m_round_finished)
		{
			m_round_finished = true;
			++m_max_depth;
			float beta = std::numeric_limits<float>::max();
			float alpha = -beta;
			minimax(m_board_index, 0, mockup, alpha, beta);
		}
	}
	m_controller->add_command(std::move(m_best_move));
	m_controller->step();
}

const char* ai::minimax_ai::get_name() const
{
	return "MinimaxAI";
}

bool ai::minimax_ai::init(std::vector<std::pair<std::string, std::string>> args)
{
	for (auto && arg : args)
	{
		if(arg.first == "time")
		{
			m_time = std::stoi(arg.second);
		}
		else if(arg.first == "depth")
		{
			m_fixed_depth = true;
			m_max_depth = std::stoi(arg.second);
		}
		else if(arg.first == "abpruning")
		{
			if(arg.second == "true")
			{
				m_abpruning = true;
			}
			else
			{
				m_abpruning = false;
			}
		}
		else if(arg.first == "pastround")
		{
			if (arg.second == "true")
			{
				m_past_rounds = true;
			}
			else
			{
				m_past_rounds = false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}
