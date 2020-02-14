#include "game_controller.h"
#include "init_round.h"
#include "tile_wall.h"
#include "score_wall_tile.h"
#include "tally_floor.h"

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

bool game_controller::step()
{
	if(current_command == m_commands.size())
	{
		if (m_model->round_finished())
		{
			add_wall_tiling_faze();
			return step();
		}
		return false;
	}
	m_commands[current_command]->Execute();
	current_command++;
	return true;
}
