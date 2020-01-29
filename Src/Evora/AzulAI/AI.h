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
		virtual const char* get_name() const = 0;
		AI(std::shared_ptr<model::game> model):m_model(model){};
	};
}
