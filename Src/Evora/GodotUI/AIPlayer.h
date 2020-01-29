#pragma once
#include "Player.h"
#include "AI.h"

namespace godot
{
	class AIPlayer :public Player
	{
		std::unique_ptr<AI::AI> player;
	};
}
