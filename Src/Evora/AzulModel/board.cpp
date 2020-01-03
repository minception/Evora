#include "board.h"

namespace model
{
	board::board()
	{
		for (int i = 0; i < COLORS; i++)
		{
			m_pattern_lines.emplace_back(i + 1);
		}
	}
}
