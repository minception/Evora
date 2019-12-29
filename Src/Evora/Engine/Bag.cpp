#include "Bag.h"

#include<algorithm>

namespace engine {
	bag::bag(int numberOfTiles)
	{
		std::random_device seed;
		m_rng = std::default_random_engine{ seed() };
	}
	void bag::generateTiles()
	{
		for (size_t i = 0; i < RED_TILES; i++)
		{
			m_tiles.emplace_back(type::red);
		}
		for (size_t i = 0; i < YELLOW_TILES; i++)
		{
			m_tiles.emplace_back(type::yellow);
		}
		for (size_t i = 0; i < BLUE_TILES; i++)
		{
			m_tiles.emplace_back(type::blue);
		}
		for (size_t i = 0; i < BLACK_TILES; i++)
		{
			m_tiles.emplace_back(type::black);
		}
		for (size_t i = 0; i < WHITE_TILES; i++)
		{
			m_tiles.emplace_back(type::white);
		}
	}
	void bag::shuffle()
	{
		std::shuffle(m_tiles.begin(), m_tiles.end(), m_rng);
	}
}
