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
		int holding_count;
		int animating_count;
		
		static void _register_methods();
		void _ready();
		void _init();
		void add_tile(Vector2 position, model::tile color, int factory);
		void tile_following(int factory, int color);
		void tile_dropped(int factory, int color);
		void tile_moved(Vector2 position, int color);
		void tile_mouse_entered(int factory, int color);
		void tile_mouse_exited(int factory, int color);
		void snap_back(int factory, int color);
		void remove_from_game(int factory_index, int color);
		void move_tiles(int factory_index, int color, const std::vector<Vector2>& positions);
		void animation_started();
		void animation_finished();
	};
}
