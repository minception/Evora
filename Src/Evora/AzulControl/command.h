#pragma once
#include "game.h"
#include <memory>
#include <utility>

namespace control
{
	class command
	{
	protected:
		std::shared_ptr<model::game> m_game;
	public:
		virtual ~command() = default;
		virtual void Execute() = 0;
		virtual void Unexecute() = 0;
		command(std::shared_ptr<model::game> game) :m_game(std::move(game)) {}
	};
}
