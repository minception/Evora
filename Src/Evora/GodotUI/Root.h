#pragma once
#include <core/Godot.hpp>
#include <Node2D.hpp>

namespace godot
{
	class Root :public Node2D
	{
		GODOT_CLASS(Root, Node2D)
	public:
		static void _register_methods();
		void _init();
	};
}
