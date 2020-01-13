#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Resource.hpp>
#include <ResourceLoader.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include "Root.h"
#include <Texture.hpp>

namespace godot
{
	class FactoryLoader :public KinematicBody2D
	{
		GODOT_CLASS(FactoryLoader, KinematicBody2D)
	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _process(float delta);

		FactoryLoader();
	};
}
