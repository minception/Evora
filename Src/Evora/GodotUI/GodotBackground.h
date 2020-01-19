#pragma once
#include <core/Godot.hpp>
#include <TextureRect.hpp>

namespace godot
{
	class GodotBackground: public TextureRect
	{
	GODOT_CLASS(GodotBackground, TextureRect)
	public:
		void _register_methods();
		void _init();
		void _ready();
		void _on_window_resize();
	
	};
}
