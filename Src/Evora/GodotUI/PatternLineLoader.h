#pragma once
#include <core/Godot.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include <Control.hpp>

namespace godot
{
	class PatternLineLoader :public Control
	{
		GODOT_CLASS(PatternLineLoader, Control)
		static Ref<PackedScene> pattern_line_scene;
	public:
		static void _register_methods();
		void _init();
		void _ready();
	};
}
