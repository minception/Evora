#pragma once
#include <core/Godot.hpp>
#include <Node2D.hpp>
namespace godot
{
	class Factory: public Node2D
	{
		GODOT_CLASS(Factory, Node2D)
	public:
		static void _register_methods();
		void _init();
		Vector2 tile_position(int index, Vector2 tile_size);
	};
}

