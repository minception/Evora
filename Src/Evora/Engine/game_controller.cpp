﻿#include "game_controller.h"
#include "init_round.h"
#include "tile_wall.h"
#include "score_wall_tile.h"
#include "tally_floor.h"
#include "score_color.h"
#include "score_line.h"
#include "score_row.h"
#include "factory_offer.h"
#include "drop_factory.h"
#include "center_offer.h"
#include "drop_center.h"

using namespace control;

void game_controller::add_wall_tiling_faze()
{
	bool final_wall_tiling = false;
	for (int player_index = 0; player_index < m_model->player_count(); ++player_index)
	{
		for (int pattern_line = 0; pattern_line < model::COLORS; ++pattern_line)
		{
			if(m_model->pattern_line_full(player_index, pattern_line))
			{
				model::tile color = m_model->pattern_line_color(player_index, pattern_line);
				m_commands.emplace_back(std::make_unique<tile_wall>(player_index, pattern_line));
				m_commands.emplace_back(std::make_unique<score_wall_tile>(player_index, pattern_line, color));
				if(m_model->wall_line_count(player_index, pattern_line) == model::COLORS - 1)
				{
					final_wall_tiling = true;
				}
			}
		}
		m_commands.emplace_back(std::make_unique<tally_floor>(player_index));
	}
	if(!final_wall_tiling)
	{
		m_commands.emplace_back(std::make_unique<init_round>());
	}
}

game_controller::game_controller(const game_controller& other)
{
	m_model = std::make_unique<model::game>(*other.m_model);
}

void game_controller::start_game()
{
	m_commands.emplace_back(std::make_unique<init_round>());
	step();
}

void game_controller::add_command(std::unique_ptr<command> command)
{
	m_commands.push_back(std::move(command));
}

void game_controller::set_first_player(int player_index)
{
	m_model->set_first_player(player_index);
}

void game_controller::add_game_end()
{
	for (int player_index = 0; player_index < m_model->player_count(); ++player_index)
	{
		for (int line = 0; line < model::COLORS; ++line)
		{
			m_commands.emplace_back(std::make_unique<score_line>(player_index, line));
		}
		for (int row = 0; row < model::COLORS; ++row)
		{
			m_commands.emplace_back(std::make_unique<score_row>(player_index, row));
		}
		for (int j = 0; j < model::COLORS; ++j)
		{
			model::tile color = (model::tile)j;
			m_commands.emplace_back(std::make_unique<score_color>(player_index, color));
		}
	}
}

std::vector<std::unique_ptr<command>> game_controller::get_possible_moves(int player_index)
{
	std::vector<std::unique_ptr<command>> commands;
	std::vector<model::tile> center_colors = m_model->get_center_colors();
	// all center to pattern line moves
	for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
	{
		for (auto&& color : center_colors)
		{
			if (m_model->can_add_to_pattern_line(player_index, pattern_line_index, color))
			{
				commands.push_back(std::move(std::make_unique<center_offer>(player_index, pattern_line_index, color)));
			}
		}
	}
	// all center to floor moves
	for (auto&& color : center_colors)
	{
		commands.push_back(std::move(std::make_unique<drop_center>(player_index, color)));
	}
	for (int factory_index = 0; factory_index < m_model->factory_count(); ++factory_index)
	{
		std::vector<model::tile> factory_colors = m_model->get_factory_colors(factory_index);
		//all factory to pattern line moves
		for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
		{
			for (auto&& color: factory_colors)
			{
				if(m_model->can_add_to_pattern_line(player_index, pattern_line_index, color))
				{
					commands.push_back(std::move(std::make_unique<factory_offer>(factory_index, player_index, pattern_line_index, color)));
				}
			}
		}
		// all factory to floor moves
		for(auto&& color: factory_colors)
		{
			commands.push_back(std::move(std::make_unique<drop_factory>(factory_index, player_index, color)));
		}
	}
	return commands;
}

/**
 * \brief Performs a single step from a command queue, if either a round is over or the game is over, adds appropriate commands to the queue
 * \return True if a step occured
 */
bool game_controller::step()
{
	if(m_current_command == m_commands.size())
	{
		if (m_game_over) return false;
		if(m_model->game_over())
		{
			add_game_end();
			m_game_over = true;
			return step();
		}
		if (m_model->round_finished())
		{
			add_wall_tiling_faze();
			return step();
		}
		return false;
	}
	m_commands[m_current_command++]->Execute(m_model);
	return true;
}

bool game_controller::is_round_over()
{
	return m_model->round_finished();
}

void game_controller::step_back()
{
	m_commands[--m_current_command]->Unexecute(m_model);
	m_commands.erase(m_commands.begin() + m_current_command, m_commands.end());
}

int game_controller::evaluate_state(int player_index)
{
	int score = 0;
	for (int i = 0; i < model::COLORS; ++i)
	{
		if(m_model->pattern_line_full(player_index, i))
		{
			score += m_model->get_pattern_line_score(player_index, i);
		}
	}
	score += m_model->get_floor_score(player_index);
	return score;
}

bool game_controller::game_over()
{
	return m_game_over;
}

int game_controller::get_winner()
{
	return m_model->get_winner();
}

int game_controller::get_first_player()
{
	return m_model->get_first_player();
}

std::shared_ptr<model::game> game_controller::get_model()
{
	return m_model;
}
