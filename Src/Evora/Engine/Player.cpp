#include "Player.h"

namespace engine {
	const std::array<int32_t, player::FLOOR_SIZE> player::FLOOR_SCORE = { -1, -1, -2, -2, -2, -3, -3 };
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
}
