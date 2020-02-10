#include "tile_wall.h"

void control::tile_wall::Execute()
{
	m_color = m_game->tile_wall(m_player_index, m_pattern_line_index);
}

void control::tile_wall::Unexecute()
{
}
