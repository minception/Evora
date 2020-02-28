#include "game.h"

namespace model
{
	game::game(int number_of_players)
	{
		const int number_of_factories = number_of_players * 2 + 1;
		for (int i = 0; i < number_of_factories; i++)
		{
			m_factories.emplace_back();
		}
		for (int i = 0; i < number_of_players; i++)
		{
			m_boards.emplace_back();
		}
		m_starter_tile_handled = false;
	}

	int game::factory_count()
	{
		return static_cast<int>(m_factories.size());
	}

	int game::player_count()
	{
		return static_cast<int>(m_boards.size());
	}

	std::vector<factory>::const_iterator game::factories_begin() const
	{
		return m_factories.cbegin();
	}

	std::vector<factory>::const_iterator game::factories_end() const
	{
		return m_factories.cend();
	}

	std::vector<board>::const_iterator game::players_begin() const
	{
		return m_boards.cbegin();
	}

	std::vector<board>::const_iterator game::players_end() const
	{
		return m_boards.cend();
	}

	std::vector<tile>::const_iterator game::center_begin() const
	{
		return m_center.begin();
	}

	std::vector<tile>::const_iterator game::center_end() const
	{
		return m_center.end();
	}

	void game::shuffle_bag()
	{
		m_bag.shuffle();
	}

	int game::bag_to_factories()
	{
		int res = 0;
		for (auto && factory : m_factories)
		{
			res += factory.fill(m_bag);
			if (m_bag.empty()) return res;
		}
		return res;
	}

	int game::factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color)
	{
		int res(0);
		while(!m_boards[player_index].pattern_line_full(pattern_line_index))
		{
			if (m_factories[factory_index].pick_color_tile(color))
			{
				m_boards[player_index].add_to_pattern_line(pattern_line_index, color);
				++res;
			}
			else break;
		}
		return res;
	}

	int game::factory_to_floor(int factory_index, int player_index, tile color)
	{
		int res(0);
		while (!m_boards[player_index].floor_full())
		{
			if (m_factories[factory_index].pick_color_tile(color))
			{
				m_boards[player_index].add_to_floor(color);
				++res;
			}
			else break;
		}
		return res;
	}

	int game::factory_to_lid(int factory_index, tile color)
	{
		int res(0);
		while (m_factories[factory_index].pick_color_tile(color))
		{
			m_lid.add_tile(color);
			++res;
		}
		return res;
	}

	int game::factory_to_center(int factory_index)
	{
		return m_factories[factory_index].add_to_center(m_center);
	}

	bool game::handle_starter_tile(int player_index)
	{
		if(!m_starter_tile_handled
			&& m_boards[player_index].has_starter_tile())
		{
			m_center.add_tile(tile::starter);
			m_boards[player_index].take_starter_tile();
			m_starter_tile_handled = true;
			return true;
		}
		return false;
	}

	bool game::can_add_to_pattern_line(int player_index, int pattern_line_index, tile color)
	{
		return m_boards[player_index].can_add_to_pattern_line(pattern_line_index, color);
	}

	std::vector<int> game::get_center_tile_indices(tile color)
	{
		return m_center.get_tile_indices(color);
	}

	int game::center_to_pattern_line(int player_index, int pattern_line_index, tile color)
	{
		int res(0);
		while (!m_boards[player_index].pattern_line_full(pattern_line_index))
		{
			if (m_center.pick_color_tile(color))
			{
				m_boards[player_index].add_to_pattern_line(pattern_line_index, color);
				++res;
			}
			else break;
		}
		return res;
	}

	int game::center_to_floor(int player_index, tile color)
	{
		int res(0);
		while (!m_boards[player_index].floor_full())
		{
			if (m_center.pick_color_tile(color))
			{
				m_boards[player_index].add_to_floor(color);
				++res;
			}
			else break;
		}
		return res;
	}

	int game::center_to_lid(tile color)
	{
		int res(0);
		while (m_center.pick_color_tile(color))
		{
			m_lid.add_tile(color);
			++res;
		}
		return res;
	}

	bool game::handle_center_starter_tile(int player_index)
	{
		if (m_center.pick_starter_tile())
		{
			m_boards[player_index].set_starter_player();
			m_boards[player_index].add_to_floor(tile::starter);
			return true;
		}
		return false;
	}

	void game::set_first_player(int player_index)
	{
		m_boards[player_index].set_starter_player();
	}

	int game::get_first_player()
	{
		for(int i = 0; i < player_count(); ++i)
		{
			if (m_boards[i].has_starter_tile()) return i;
		}
		return -1;
	}

	void game::starter_tile_unhandled()
	{
		m_starter_tile_handled = false;
	}

	bool game::round_finished()
	{
		if (!m_center.empty()) return false;
		for(auto&& factory: m_factories)
		{
			if(!factory.empty())
			{
				return false;
			}
		}
		return true;
	}

	tile game::tile_wall(int player_index, int pattern_line_index)
	{
		tile color = m_boards[player_index].pattern_line_color(pattern_line_index);
		m_boards[player_index].clear_pattern_line(pattern_line_index);
		m_boards[player_index].tile_wall(pattern_line_index, color);
		m_lid.add_tiles(pattern_line_index, color);
		return color;
	}

	int game::score_wall_tile(int player_index, int pattern_line_index, tile tile)
	{
		return m_boards[player_index].score_wall_tile(pattern_line_index, tile);
	}

	std::vector<int> game::get_score_indices(int player_index, int pattern_line_index, tile tile)
	{
		return m_boards[player_index].get_score_indices(pattern_line_index, tile);
	}

	tile game::pattern_line_color(int player_index, int pattern_line_index)
	{
		return m_boards[player_index].pattern_line_color(pattern_line_index);
	}

	bool game::pattern_line_full(int player_index, int pattern_line_index)
	{
		return m_boards[player_index].pattern_line_full(pattern_line_index);
	}

	int game::score_floor(int player_index)
	{
		return m_boards[player_index].score_floor();
	}

	int game::floor_to_lid(int player_index)
	{
		return m_boards[player_index].floor_to_lid(m_lid);
	}

	int game::handle_floor_starter_tile(int player_index)
	{
		return m_boards[player_index].handle_floor_starter_tile();
	}

	bool game::game_over()
	{
		for(auto&& board:m_boards)
		{
			if(board.game_finished())
			{
				return true;
			}
		}
		return false;
	}

	int game::score_wall_color(int player_index, tile color)
	{
		return m_boards[player_index].score_wall_color(color);
	}

	int game::score_wall_line(int player_index, int line)
	{
		return m_boards[player_index].score_wall_line(line);
	}

	int game::score_wall_row(int player_index, int row)
	{
		return m_boards[player_index].score_wall_row(row);
	}

	std::vector<model::tile> game::get_center_colors()
	{
		return m_center.get_colors();
	}

	std::vector<model::tile> game::get_factory_colors(int factory_index)
	{
		return m_factories[factory_index].get_colors();
	}

	int game::get_winner()
	{
		int max_score = 0;
		int winner_index = 0;
		for (int i = 0; i < m_boards.size(); ++i)
		{
			if(m_boards[i].get_score() > max_score)
			{
				winner_index = i;
			}
		}
		return winner_index;
	}

	int game::wall_line_count(int player_index, int line)
	{
		return m_boards[player_index].wall_line_count(line);
	}

	int game::get_floor_score(int player_index)
	{
		return m_boards[player_index].get_floor_score();
	}

	int game::get_pattern_line_score(int player_index, int pattern_line_index)
	{
		return m_boards[player_index].get_pattern_line_score(pattern_line_index);
	}

	std::unique_ptr<game> game::clone()
	{
		return std::unique_ptr<game>(new game(*this));
	}

	std::vector<tile> game::get_lid_state()
	{
		return m_lid.get_state();
	}

	void game::refill_bag()
	{
		m_bag.refill(m_lid); 
	}
}
