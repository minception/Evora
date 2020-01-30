#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include <Node2D.hpp>
#include <vector>
#include "Factory.h"

namespace godot
{
	class FactoryLoader :public Node2D
	{
		GODOT_CLASS(FactoryLoader, KinematicBody2D)
		Ref<PackedScene> m_factory_scene;
		std::vector<Node2D> m_factories;
	public:
		static void _register_methods();
		void _ready();
		static void _init();
		static void _process(float delta);
		void load_factories(int count, Vector2 c, float r);

		FactoryLoader();
	};
}
