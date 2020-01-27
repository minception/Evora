#pragma once
#include "command.h"

namespace control
{
	class tile_wall :public command
	{
	public:
		tile_wall(std::shared_ptr<model::game> game, int pattern_line_index, model::tile color)
			: command(game),
			  m_pattern_line_index(pattern_line_index),
			  m_color(color)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_pattern_line_index; // here moved to lid would be always equal to pattern line index
		model::tile m_color;
		int m_score;
	};
}
