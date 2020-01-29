#pragma once
#include "Player.h"

namespace godot
{
	class HumanPlayer :public Player
	{
	public:
		void move() override;
	};
}

