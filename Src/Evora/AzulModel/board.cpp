#include "player.h"
namespace model
{
	player::player()
	{
		for (int i = 0; i < COLORS; i++)
		{
			m_wall.emplace_back();
			for (int j = 0; j < COLORS; j++)
			{
				m_wall[i].emplace_back(empty);
			}
		}
		for (int i = 0; i < COLORS; i++)
		{
			m_pattern_lines.emplace_back();
			for (int j = 0; j <= i; j++)
			{
				m_pattern_lines[i].emplace_back(empty);
			}
		}
	}
}
