#pragma once
#include "game.h"

namespace AI
{
	class AI
	{
		model::game m_model;
	public:
		virtual void move() = 0;
		AI(model::game m_model);
	};
}
