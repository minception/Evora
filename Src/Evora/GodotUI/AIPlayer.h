#pragma once
#include "Player.h"
#include "ai.h"
#include <thread>

namespace godot
{
	class AIPlayer :public Player
	{
		std::unique_ptr<ai::ai> m_player;
		std::thread m_worker;
	public:
		void move() override;
		AIPlayer(std::unique_ptr<ai::ai> player) :m_player(std::move(player)){}
	};
}
