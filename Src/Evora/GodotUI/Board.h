#pragma once

#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>

namespace godot {
	class Board : public KinematicBody2D {
		GODOT_CLASS(Board, KinematicBody2D)
	private:
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

		Board();
		~Board();
	};
}