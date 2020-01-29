#pragma once
#include "Player.h"
#include "AI.h"

namespace godot
{
	class AIPlayer :public Player
	{
		std::unique_ptr<AI::AI> m_player;
	public:
		void move() override;
		AIPlayer(std::unique_ptr<AI::AI> player) :m_player(std::move(player)){}
	};
}
