#pragma once
#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <vector>

namespace godot
{
	class ColorHighlight :public Node2D
	{
		GODOT_CLASS(ColorHighlight, Node2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void highlight(std::vector<Vector2> positions);
		void unhighlight();
	};
}
