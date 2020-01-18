#pragma once
#include "game.h"
#include <memory>

namespace AI
{
	class AI
	{
		std::shared_ptr<model::game> m_model;
	public:
		virtual void move() = 0;
		AI(std::shared_ptr<model::game> model):m_model(model){};
	};
}
