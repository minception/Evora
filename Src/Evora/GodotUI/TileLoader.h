#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <core/Ref.hpp>
#include "Root.h"
#include <Texture.hpp>
#include "tile.h"

namespace godot
{
	class Root;
	class TileLoader :public Node2D
	{
		GODOT_CLASS(TileLoader, Node2D)
	public:
		static Root* p_root;
		int holding_color;
		
		static void _register_methods();
		void _ready();
		void _init();
		void add_tile(Vector2 position, model::tile color, int factory);
		void tile_following(int factory, int color);
		void tile_dropped(int factory, int color);
		void tile_mouse_entered(int factory, int color);
		void tile_mouse_exited(int factory, int color);
	};
}
