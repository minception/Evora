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
		virtual void Execute(std::shared_ptr<model::game> game) = 0;
		virtual void Unexecute(std::shared_ptr<model::game> game) = 0;
		virtual bool IsMove() = 0;
		virtual std::unique_ptr<command> clone() = 0;
	};
}
