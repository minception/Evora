#pragma once

#include <core/Godot.hpp>
#include <TextureRect.hpp>

namespace godot {
	class GodotTile : public TextureRect {
		GODOT_CLASS(GodotTile, TextureRect)
	private:
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

		GodotTile();
	};
}
