#pragma once

#include <core/Godot.hpp>
#include <memory>
#include <Node2D.hpp>

#include "GodotGame.h"
#include "Board.h"
#include "GodotTile.h"


namespace godot
{
	class GodotGame;
	class TileLoader;
	class Root :public Node2D
	{
		GODOT_CLASS(Root, Node2D)
		std::shared_ptr<GodotGame> m_game;
		int number_of_players;
		int current_player;
		int holding_color;
		int holding_count;
	public:
		static void _register_methods();
		void _init();
		void _ready();
	};
}
