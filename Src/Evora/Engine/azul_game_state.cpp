#include "azul_game_state.h"
#include "azul_game_move.h"

#include "game.h"
#include <memory>
#include <memory>
#include <memory>
#include <memory>

azul_game_state::azul_game_state(std::shared_ptr<control::game_controller> state, int player) :
	m_player_who_just_moved(player),
	m_winner(0),
	m_not_win(true),
	m_state(state)
{
	calculate_moves();
	std::random_device rndDevice;
	m_rng = std::make_shared<std::mt19937>(rndDevice());
}

std::shared_ptr<game_state> azul_game_state::clone() const
{
	auto cloned = std::make_shared<azul_game_state>(*this);
	cloned->m_state = std::make_shared<control::game_controller>(*m_state);
	return cloned;
}

std::vector<std::shared_ptr<const game_move>> azul_game_state::get_moves() const
{
	return m_moves;
}

void azul_game_state::do_move(const game_move& move)
{
	const azul_game_move& azulMove = dynamic_cast<const azul_game_move&>(move);
	std::unique_ptr<control::command> command = azulMove.generate_command(m_player_who_just_moved);
	m_state->add_command(std::move(command));
 	while (m_state->step())
	{
	}
	m_player_who_just_moved = m_state->get_current_player();
	calculate_moves();
	if(is_terminal())
	{
		m_winner = m_state->get_winner();
		m_not_win = false;
	}
}

double azul_game_state::get_result(int player) const
{
	if (m_winner == player)
	{
		return 1.0;
	}
	return 0.0;
}

int azul_game_state::get_winner() const
{
	return m_winner;
}

const game_move& azul_game_state::get_simulation_move() const
{
	std::uniform_real_distribution<float> dist(0, m_total_weight);
	float randomNumber = dist(*m_rng);
	int moveIndex = 0;
	float weightSum = 0.f;
	while(moveIndex < m_moves.size())
	{
		weightSum += m_move_weights[moveIndex];
		if(weightSum < randomNumber)
		{
			moveIndex++;
		}
		else
		{
			break;
		}
	}
	return *m_moves[moveIndex];
}

int azul_game_state::get_player_who_just_moved() const
{
	return m_player_who_just_moved;
}

bool azul_game_state::is_terminal() const
{
	return m_state->game_over();
}

std::shared_ptr<const game_move> azul_game_state::parse_move(const std::string& move) const
{
	return std::dynamic_pointer_cast<const game_move>(std::make_shared<const azul_game_move>(stoi(move)));
}

void azul_game_state::addMove(int factory_index, int pattern_line_index, int color, float weight)
{
	int move = factory_index | (pattern_line_index << 4) | (color << 8);
	m_moves.push_back(std::make_shared<azul_game_move>(move));
	m_move_weights.push_back(weight);
	m_total_weight += weight;
}

void azul_game_state::calculate_moves()
{
	if (m_not_win)
	{
		m_total_weight = 0;
		m_moves.clear();
		m_move_weights.clear();
		for (int factory_index = 0; factory_index <= m_state->get_model()->factory_count(); ++factory_index)
		{
			std::vector<model::tile> colors;
			if(factory_index == m_state->get_model()->factory_count())
			{
				colors = m_state->get_model()->get_center_colors();
			}
			else
			{
				colors = m_state->get_model()->get_factory_colors(factory_index);
			}
			for (auto&& color : colors)
			{
				for(int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
				{
					if(m_state->get_model()->can_add_to_pattern_line(m_player_who_just_moved, pattern_line_index, color))
					{
						add_move(factory_index, pattern_line_index, (int)color, 1.0f);
					}
				}
				// for every color adding move to floor
				add_move(factory_index, model::COLORS, (int)color, 0.05f);
			}
		}
	}
}
