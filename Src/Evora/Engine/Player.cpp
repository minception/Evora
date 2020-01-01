#include "Player.h"

namespace engine {
	const std::array<int32_t, player::FLOOR_SIZE> player::FLOOR_SCORE = { -1, -1, -2, -2, -2, -3, -3 };

	int player::first_empty_spot(size_t patternLine)
	{
		for (size_t i = 0; i < m_patternLine[patternLine].size(); i++)
		{
			if(m_patternLine[patternLine][i].is_empty())
			{
				return i;
			}
		}
		return -1;
	}

	player::player()
	{
		// init wall
		for (size_t i = 0; i < WALL_SIZE; ++i)
		{
			m_wall.emplace_back();
			for (size_t j = 0; j < WALL_SIZE; ++j)
			{
				m_wall[i].emplace_back(type::empty);
			}
		}
		// init pattern lines
		for (size_t i = 0; i < PATTERN_LINE_SIZE; ++i)
		{
			m_patternLine.emplace_back();
			for (size_t j = 0; j < i + 1; ++j)
			{
				m_patternLine[i].emplace_back(type::empty);
			}
		}
		// init floor
		for (size_t i = 0; i < FLOOR_SIZE; ++i)
		{
			m_floor.emplace_back(type::empty);
		}
	}

	matrix_line_iterator player::wall_begin() const
	{
		return m_wall.cbegin();
	}

	matrix_line_iterator player::wall_end() const
	{
		return m_wall.cend();
	}

	matrix_line_iterator player::pattern_lines_begin() const
	{
		return m_patternLine.cbegin();
	}

	matrix_line_iterator player::pattern_lines_end() const
	{
		return m_patternLine.cend();
	}

	floor_iterator player::floor_begin() const
	{
		return m_floor.cbegin();
	}

	floor_iterator player::floor_end() const
	{
		return m_floor.cend();
	}

	int32_t player::get_score() const
	{
		return m_score;
	}

	bool player::put_to_floor(type type)
	{
		if(m_floor.size() < FLOOR_SIZE)
		{
			m_floor.emplace_back(type);
			return true;
		}
		return false;
	}

	bool player::put_to_pattern_line(size_t patternLine, type color, size_t count)
	{
		if(m_patternLine[patternLine].front().get_type() == type::empty
			|| m_patternLine[patternLine].front().get_type() == color)
		{
			const int first_empty_index = first_empty_spot(patternLine);
			if(first_empty_index == -1)
			{
				return false;
			}
			for (size_t i = first_empty_index; i < count; i++)
			{
				if(i == m_patternLine[patternLine].size())
				{
					for (size_t j = i; j < count; j++)
					{
						put_to_floor(color);
						// TODO: if this returns false, throw the remaining stones to the lid
					}
					break;
				}
				m_patternLine[patternLine][i].set_type(color);
			}
			return true;
		}
		return false;
	}
}
