#pragma once
#include "command.h"

namespace control
{
	class tile_wall :public command
	{
	public:
		tile_wall(std::shared_ptr<model::game> game, int player_index, int pattern_line_index)
			: command(game),
			  m_player_index(player_index),
			  m_pattern_line_index(pattern_line_index)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		int m_pattern_line_index; // here moved to lid would be always equal to pattern line index
		model::tile m_color;
	};
}
