#pragma once
#include <memory>
#include <utility>
#include "game.h"

namespace control
{
	class command
	{
	public:
		virtual ~command() = default;
		virtual void execute(std::shared_ptr<model::game> game) = 0;
		virtual void unexecute(std::shared_ptr<model::game> game) = 0;
		virtual bool is_move() = 0;
		virtual int player_index() = 0;
		virtual std::unique_ptr<command> clone() = 0;
	};
}
