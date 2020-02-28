#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <PackedScene.hpp>
#include <Node2D.hpp>

namespace godot
{
	class FactoryLoader :public Node2D
	{
		GODOT_CLASS(FactoryLoader, Node2D)
	public:
		static void _register_methods();
		void _ready();
		static void _init();
		static void _process(float delta);
		void load_factories(int count, Vector2 c, float r);
	};
}
