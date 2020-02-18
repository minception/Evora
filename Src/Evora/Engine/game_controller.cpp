#include "game_controller.h"
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
	for (int i = 0; i < m_model->player_count(); ++i)
	{
		for (int j = 0; j < model::COLORS; ++j)
		{
			if(m_model->pattern_line_full(i, j))
			{
				model::tile color = m_model->pattern_line_color(i, j);
				m_commands.emplace_back(std::make_unique<tile_wall>(m_model, i, j));
				m_commands.emplace_back(std::make_unique<score_wall_tile>(m_model, i, j, color));
			}
		}
		m_commands.emplace_back(std::make_unique<tally_floor>(m_model, i));
	}
	m_commands.emplace_back(std::make_unique<init_round>(m_model));
}

void game_controller::start_game()
{
	m_commands.emplace_back(std::make_unique<init_round>(m_model));
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
	for (int i = 0; i < m_model->player_count(); ++i)
	{
		for (int line = 0; line < model::COLORS; ++line)
		{
			m_commands.emplace_back(std::make_unique<score_line>(m_model, i, line));
		}
		for (int row = 0; row < model::COLORS; ++row)
		{
			m_commands.emplace_back(std::make_unique<score_row>(m_model, i, row));
		}
		for (int j = 0; j < model::COLORS; ++j)
		{
			model::tile color = (model::tile)j;
			m_commands.emplace_back(std::make_unique<score_color>(m_model, i, color));
		}
	}
}

std::vector<std::unique_ptr<command>> game_controller::get_possible_moves(int player_index)
{
	std::vector<std::unique_ptr<command>> commands;
	std::vector<model::tile> center_colors = m_model->get_center_colors();
	for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
	{
		for (auto&& color : center_colors)
		{
			if (m_model->can_add_to_pattern_line(player_index, pattern_line_index, color))
			{
				commands.push_back(std::move(std::make_unique<center_offer>(m_model, player_index, pattern_line_index, color)));
			}
		}
	}
	for (auto&& color : center_colors)
	{
		commands.push_back(std::move(std::make_unique<drop_center>(m_model, player_index, color)));
	}
	for (int factory_index = 0; factory_index < m_model->factory_count(); ++factory_index)
	{
		std::vector<model::tile> factory_colors = m_model->get_factory_colors(factory_index);
		for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
		{
			for (auto&& color: factory_colors)
			{
				if(m_model->can_add_to_pattern_line(player_index, pattern_line_index, color))
				{
					commands.push_back(std::move(std::make_unique<factory_offer>(m_model, factory_index, player_index, pattern_line_index, color)));
				}
			}
		}
		for(auto&& color: factory_colors)
		{
			commands.push_back(std::move(std::make_unique<drop_factory>(m_model, factory_index, player_index, color)));
		}
	}
	return commands;
}

bool game_controller::step()
{
	if(current_command == m_commands.size())
	{
		if(m_model->game_over())
		{
			add_game_end();
			return step();
		}
		if (m_model->round_finished())
		{
			add_wall_tiling_faze();
			return step();
		}
		return false;
	}
	m_commands[current_command++]->Execute();
	return true;
}
