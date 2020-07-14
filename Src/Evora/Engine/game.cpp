#include "game.h"

namespace model
{
	/**
	 * \brief Creates a game instance with a given number of players
	 * \param number_of_players Number of players in game
	 */
	game::game(int number_of_players, int seed) : m_bag()
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

		std::random_device rand;
		seed = seed >= 0 ? seed : rand();
		m_rng = std::make_shared<std::mt19937>(seed);
	}

	/**
	 * \brief Number of factories in the game instance
	 * \return Number of factories
	 */
	int game::factory_count()
	{
		return static_cast<int>(m_factories.size());
	}

	/**
	 * \brief Number of players in the game instance
	 * \return Number of players
	 */
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

	/**
	 * \brief Randomly shuffles the content of the bag
	 */
	void game::shuffle_bag()
	{
		m_bag.shuffle(m_rng);
	}

	/**
	 * \brief Moves the tiles from bag to factories
	 * \return Number of tiles moved from bag to factories
	 */
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

	/**
	 * \brief Moves tiles of a given color from a chosen factory to a chosen pattern line
	 * \param factory_index Factory index
	 * \param player_index Player index
	 * \param pattern_line_index Pattern line index
	 * \param color Color of tiles to move
	 * \return Number of tiles moved from factory to pattern line
	 */
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

	/**
	 * \brief Moves tiles of a given color from a chosen factory to the floor of a chosen player
	 * \param factory_index Factory index
	 * \param player_index Player index
	 * \param color Color of tiles to move
	 * \return Number of tiles moved to the floor
	 */
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

	/**
	 * \brief Moves tiles of a given color from chosen factory to the lid
	 * \param factory_index Factory index
	 * \param color Color of tiles to move
	 * \return Number of tiles moved to the lid
	 */
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

	/**
	 * \brief Moves all the tiles from a given factory to the center
	 * \param factory_index Factory index
	 * \return Number of tiles moved to a center
	 */
	int game::factory_to_center(int factory_index)
	{
		return m_factories[factory_index].add_to_center(m_center);
	}

	/**
	 * \brief If the tile was not handled yet in the current round, it is given to an appropriate player
	 * \param player_index Player index
	 * \return Whether or not the tile was handled
	 */
	bool game::handle_starter_tile(int player_index)
	{
		if(!m_starter_tile_handled
			&& m_boards[player_index].has_starter_tile())
		{
			m_center.add_starter_tile();
			m_boards[player_index].take_starter_tile();
			m_starter_tile_handled = true;
			return true;
		}
		return false;
	}

	/**
	 * \brief Checks whether pattern line can accept a tile of a given color
	 * \param player_index Player index
	 * \param pattern_line_index Pattern line index
	 * \param color Tile color
	 * \return Returns true if tiles can be added, false otherwise
	 */
	bool game::can_add_to_pattern_line(int player_index, int pattern_line_index, tile color)
	{
		return m_boards[player_index].can_add_to_pattern_line(pattern_line_index, color);
	}

	/**
	 * \brief Indices of tiles of given color in center
	 * \param color Tile color
	 * \return Indices of tiles of given color
	 */
	std::vector<int> game::get_center_tile_indices(tile color)
	{
		return m_center.get_tile_indices(color);
	}

	/**
	 * \brief Move tiles from center to a chosen pattern line
	 * \param player_index Player index
	 * \param pattern_line_index Pattern line index
	 * \param color Color of tiles to move
	 * \return Number of tiles moved
	 */
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

	/**
	 * \brief Move maximum amount of tiles of a given color from center to floor of a chosen player
	 * \param player_index Player index
	 * \param color Color of tiles to move
	 * \return Number of tiles moved from center to floor
	 */
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

	/**
	 * \brief Move all the tiles of a given color from center to lid
	 * \param color Color of tiles to move
	 * \return Number of tiles moved to the lid
	 */
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

	/**
	 * \brief When a player is first to draw from center, he receives a starter tile
	 * \param player_index Player index
	 * \return Returns true if a starter tile was handled, false otherwise
	 */
	bool game::handle_center_starter_tile(int player_index)
	{
		if (m_center.pick_starter_tile())
		{
			m_boards[player_index].set_starter_player();
			if (!m_boards[player_index].floor_full())
			{
				m_boards[player_index].add_starter_to_floor();
			}
			return true;
		}
		return false;
	}

	/**
	 * \brief Sets a starter player at the beginning of the game
	 * \param player_index Player index
	 */
	void game::set_first_player(int player_index)
	{
		m_boards[player_index].set_starter_player();
	}

	/**
	 * \brief Get an index of the player currently holding the starter tile
	 * \return Index of the player
	 */
	int game::get_first_player()
	{
		for(int i = 0; i < player_count(); ++i)
		{
			if (m_boards[i].has_starter_tile()) return i;
		}
		return -1;
	}

	/**
	 * \brief Set whether a starter tile was handled in the current round
	 */
	void game::set_starter_tile_handled(bool val)
	{
		m_starter_tile_handled = val;
	}

	/**
	 * \brief Check whether all the factories and the center are empty
	 * \return True if round is finished false otherwise
	 */
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

	/**
	 * \brief Moves a single tile to the wall and remaining tiles to the lid, should only be called once the pattern line is full
	 * \param player_index Player index
	 * \param pattern_line_index Pattern line index and wall line index
	 * \return Color of tile moved to wall
	 */
	tile game::tile_wall(int player_index, int pattern_line_index)
	{
		tile color = m_boards[player_index].pattern_line_color(pattern_line_index);
		m_boards[player_index].clear_pattern_line(pattern_line_index);
		m_boards[player_index].tile_wall(pattern_line_index, color);
		m_lid.add_tiles(pattern_line_index, color);
		return color;
	}

	/**
	 * \brief Calculate score for a given tile on the wall and ads it to a player total
	 * \param player_index Player index
	 * \param pattern_line_index Wall line index
	 * \param tile Tile color
	 * \return Score increase after adding a tile to wall
	 */
	int game::score_wall_tile(int player_index, int pattern_line_index, tile tile)
	{
		return m_boards[player_index].score_wall_tile(pattern_line_index, tile);
	}

	/**
	 * \brief A function to see what is the span of tiles filled around a given tiles
	 * \param player_index Player index
	 * \param pattern_line_index Wall line index
	 * \param tile Tile color
	 * \return A vector containing indices representing span of filled tiles around a given tile. Respecively: horizontal start, horizontal end, vertical start, vertical end
	 */
	std::vector<int> game::get_score_indices(int player_index, int pattern_line_index, tile tile)
	{
		return m_boards[player_index].get_score_indices(pattern_line_index, tile);
	}

	/**
	 * \brief Get a color of tiles in the given pattern line
	 * \param player_index Player index
	 * \param pattern_line_index Pattern line index
	 * \return A color of tiles in a pattern line
	 */
	tile game::pattern_line_color(int player_index, int pattern_line_index)
	{
		return m_boards[player_index].pattern_line_color(pattern_line_index);
	}

	/**
	 * \brief Checks whether a pattern line is fully filled
	 * \param player_index Player index
	 * \param pattern_line_index Pattern line index
	 * \return True if a pattern line is full
	 */
	bool game::pattern_line_full(int player_index, int pattern_line_index)
	{
		return m_boards[player_index].pattern_line_full(pattern_line_index);
	}

	/**
	 * \brief Calculate a score increase from a given player floor and add the score to the player score total
	 * \param player_index Player index
	 * \return Score increase from the floor (will always be either zero or negative number)
	 */
	int game::score_floor(int player_index)
	{
		return m_boards[player_index].score_floor();
	}

	/**
	 * \brief Move all the tiles (excluding the starter tile) from the player floor to the lid
	 * \param player_index Player index
	 * \return Number of tiles moved
	 */
	int game::floor_to_lid(int player_index)
	{
		return m_boards[player_index].floor_to_lid(m_lid);
	}

	/**
	 * \brief Removes the starter tile from the player's floor
	 * \param player_index Player index
	 * \return A position of the starter tile on the floor, if not present, returns -1
	 */
	bool game::handle_floor_starter_tile(int player_index)
	{
		return m_boards[player_index].handle_floor_starter_tile();
	}

	/**
	 * \brief Checks whether any of the players has filled a full row of tiles on the wall
	 * \return True if the game is over
	 */
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

	/**
	 * \brief Adds an end game score for a given color to the player total
	 * \param player_index Player index
	 * \param color Tile color
	 * \return A score increase
	 */
	int game::score_wall_color(int player_index, tile color)
	{
		return m_boards[player_index].score_wall_color(color);
	}

	/**
	 * \brief Adds an end game score of a given wall line to the player total
	 * \param player_index Player index
	 * \param line Wall line index
	 * \return A score increase
	 */
	int game::score_wall_line(int player_index, int line)
	{
		return m_boards[player_index].score_wall_line(line);
	}

	/**
	 * \brief Adds an end game score of a given wall row to the player total
	 * \param player_index Player index
	 * \param row Wall row index
	 * \return A score increase
	 */
	int game::score_wall_row(int player_index, int row)
	{
		return m_boards[player_index].score_wall_row(row);
	}

	/**
	 * \brief Get all the colors present in the center
	 * \return Vector containing colors
	 */
	std::vector<model::tile> game::get_center_colors()
	{
		return m_center.get_colors();
	}

	/**
	 * \brief Get all the colors present in the given factory
	 * \param factory_index Factory index
	 * \return Vector containing colors
	 */
	std::vector<model::tile> game::get_factory_colors(int factory_index)
	{
		return m_factories[factory_index].get_colors();
	}

	/**
	 * \brief Get an index of a winning player
	 * \return Winner player index
	 */
	int game::get_winner()
	{
		int max_score = 0;
		int winner_index = 0;
		int max_horizontal_lines = 0;
		for (unsigned int i = 0; i < m_boards.size(); ++i)
		{
			int player_score = m_boards[i].get_score();
			if(player_score > max_score)
			{
				winner_index = i;
				max_score = player_score;
				max_horizontal_lines = m_boards[i].horizontal_lines();
			}
			// when the score is the same, the winner is the player with higher amount of horizontal lines
			else if(player_score == max_score)
			{
				int horizontal_lines = m_boards[i].horizontal_lines();
				if(horizontal_lines > max_horizontal_lines)
				{
					winner_index = i;
					max_horizontal_lines = horizontal_lines;
				}
			}
	}
		return winner_index;
	}

	/**
	 * \brief Get a number of filled tiles in a given wall line
	 * \param player_index Player index
	 * \param line Wall line index
	 * \return Number of filled tiles
	 */
	int game::wall_line_count(int player_index, int line)
	{
		return m_boards[player_index].wall_line_count(line);
	}

	/**
	 * \brief Get a floor score of a given player
	 * \param player_index Player index
	 * \return Score increase
	 */
	int game::get_floor_score(int player_index)
	{
		return m_boards[player_index].get_floor_score();
	}

	int game::get_floor_score(int player_index, int tiles)
	{
		return m_boards[player_index].get_floor_score(tiles);
	}

	int game::get_wall_tile_score(int player_index, int line, tile color)
	{
		return m_boards[player_index].get_wall_tile_score(line, color);
	}

	/**
	 * \brief get a score a given pattern line will add in the wall tiling phase
	 * \param player_index Player index
	 * \param pattern_line_index Pattern line index
	 * \return Score increase
	 */
	int game::get_pattern_line_score(int player_index, int pattern_line_index)
	{
		return m_boards[player_index].get_pattern_line_score(pattern_line_index);
	}

	int game::get_board_score(int player_index)
	{
		return m_boards[player_index].get_score();
	}

	void game::pattern_line_to_center(int player_index, int pattern_line_index, tile color, int count, std::vector<int>& is)
	{
		m_boards[player_index].remove_from_pattern_line(pattern_line_index, count);
		m_center.return_tiles(color, count, is);
	}

	void game::floor_to_center(int player_index, tile color, int count, std::vector<int>& is)
	{
		m_boards[player_index].remove_from_floor(count);
		m_center.return_tiles(color, count, is);
	}

	void game::lid_to_center(tile color, int count, std::vector<int>& is)
	{
		m_lid.remove_tiles(count);
		m_center.return_tiles(color, count, is);
	}

	void game::starter_tile_to_center(int player_index)
	{
		m_boards[player_index].take_starter_tile();
		m_center.add_starter_tile();
	}

	void game::floor_to_factory(int factory_index, int player_index, tile color, int count)
	{
		m_boards[player_index].remove_from_floor(count);
		m_factories[factory_index].add_tiles(color, count);
	}

	void game::lid_to_factory(int factory_index, tile color, int count)
	{
		m_lid.remove_tiles(count);
		m_factories[factory_index].add_tiles(color, count);
	}

	void game::center_to_factory(int factory_index, int count)
	{
		m_factories[factory_index].add_from_center(m_center, count);
	}

	void game::remove_center_starter_tile()
	{
		m_center.pick_starter_tile();
	}

	void game::pattern_line_to_factory(int factory_index, int player_index, int pattern_line_index, tile color,	int count)
	{
		m_boards[player_index].remove_from_pattern_line(pattern_line_index, count);
		m_factories[factory_index].add_tiles(color, count);
	}

	void game::factories_to_bag()
	{
		for (auto && factory : m_factories)
		{
			factory.return_to_bag(m_bag);
		}
	}

	void game::take_score(int player_index, int score)
	{
		m_boards[player_index].take_score(score);
	}

	void game::lid_to_floor(int player_index, int count)
	{
		m_boards[player_index].lid_to_floor(m_lid, count);
	}

	void game::add_starter_to_floor(int player_index)
	{
		m_boards[player_index].add_starter_to_floor();
	}

	void game::wall_to_pattern_line(int player_index, int pattern_line_index, tile tile)
	{
		m_boards[player_index].wall_to_pattern_line(pattern_line_index, tile);
		m_lid.remove_tiles(pattern_line_index);
	}

	void game::remove_tile_from_bag(tile tile)
	{
		m_bag.remove_tile(tile);
	}

	void game::set_lid_state(std::vector<tile>& tiles)
	{
		m_lid.set_state(tiles);
	}

	std::vector<std::tuple<tile, int>> game::get_center_colors_count()
	{
		return m_center.get_colors_count();
	}

	std::vector<std::tuple<tile, int>> game::get_factory_colors_count(int factory_index)
	{
		return m_factories[factory_index].get_colors_count();
	}

	int game::get_pattern_line_tile_count(int player_index, int pattern_line_index)
	{
		return m_boards[player_index].get_pattern_line_tile_count(pattern_line_index);
	}

	int game::factory_tile_count(int factory_index, tile color)
	{
		return m_factories[factory_index].tile_count(color);
	}

	int game::center_tile_count(tile color)
	{
		return m_center.tile_count(color);
	}

	/**
	 * \brief Get a copy of a current lid state
	 * \return Vector representing tiles in the lid
	 */
	std::vector<tile> game::get_lid_state()
	{
		return m_lid.get_state();
	}

	/**
	 * \brief Refills a bag from the lid
	 */
	void game::refill_bag()
	{
		m_bag.refill(m_lid); 
	}
	std::shared_ptr<std::mt19937> game::get_rng()
	{
		return m_rng;
	}
}
