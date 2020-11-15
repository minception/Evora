#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include "Player.h"
#include "GodotGame.h"

namespace godot
{
	class GameData :public Node
	{
		GODOT_CLASS(GameData, Node)
	public:
		std::vector<std::unique_ptr<Player>> players;
		std::shared_ptr<GodotGame> m_game;
		int current_player;
		int number_of_players;
		std::shared_ptr<control::game_controller> m_controller;
		static void _register_methods();
		void add_player(std::unique_ptr<Player> player);
		void _init();
		void set_data();
	};
}
