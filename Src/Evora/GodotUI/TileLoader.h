#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <core/Ref.hpp>
#include "Root.h"
#include <Texture.hpp>
#include "tile.h"

namespace godot
{
	class TileLoader :public Node2D
	{
		GODOT_CLASS(TileLoader, Node2D)
	private:
	public:
		static void _register_methods();
		void _ready();
		void _init();
		void add_tile(Vector2 position, model::tile color, int factory, int index);
		void tile_mouse_entered(int factory, int color);
		void tile_mouse_exited(int factory, int color);
		void tile_picked_up(int factory, int color);
	};
}
