#pragma once
#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <vector>
#include "GodotTile.h"

namespace godot
{
	class Factory: public Node2D
	{
		GODOT_CLASS(Factory, Node2D)
		std::vector<GodotTile*> tiles;
	public:
		static void _register_methods();
		void _init();
		void add_tile(GodotTile* tile);
		Vector2 tile_position(int index);
	};
}

