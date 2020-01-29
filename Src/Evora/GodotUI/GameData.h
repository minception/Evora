#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include "Player.h"

namespace godot
{
	class GameData :public Node
	{
		GODOT_CLASS(GameData, Node)
		std::shared_ptr<model::game> m_game;
		std::vector<std::unique_ptr<Player>> players;
	public:
		int current_player;
		int number_of_players;
		std::shared_ptr<control::game_controller> controller;
		static void _register_methods();
		void add_player(std::unique_ptr<Player> player);
		void _init();
	
	};
}
