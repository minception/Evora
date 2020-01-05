#pragma once

#include <core/Godot.hpp>
#include <TextureRect.hpp>

namespace godot {
	class Board : public TextureRect {
		GODOT_CLASS(Board, TextureRect)
	private:
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

		Board();
	};
}