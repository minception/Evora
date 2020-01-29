#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include "Player.h"

namespace godot
{
	class GameData :public Node
	{
		GODOT_CLASS(GameData, Node)
		std::vector<std::unique_ptr<Player>> players;
		int current_player;
		std::shared_ptr<control::game_controller> controller;
	public:
		static void _register_methods();
		void _init();
	
	};
}
