#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>

namespace godot
{
	class Tile :public KinematicBody2D
	{
		GODOT_CLASS(Tile, KinematicBody2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

		Tile();
	};
}
