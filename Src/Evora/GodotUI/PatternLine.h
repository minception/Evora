#pragma once
#include <core/Godot.hpp>
#include <TextureRect.hpp>

namespace godot
{
	class PatternLine :public TextureRect
	{
		GODOT_CLASS(PatternLine, TextureRect)
	public:
		int index;
		static void _register_methods();
		void _init();
	
	};
}
