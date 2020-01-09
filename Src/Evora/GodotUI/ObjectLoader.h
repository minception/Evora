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
	class ObjectLoader :public KinematicBody2D
	{
		GODOT_CLASS(ObjectLoader, KinematicBody2D)
	private:
		godot::Ref<PackedScene> tileScene;
		godot::Ref<Texture> blackTexture;
		godot::Ref<Texture> whiteTexture;
		godot::Ref<Texture> blueTexture;
		godot::Ref<Texture> redTexture;
		godot::Ref<Texture> yellowTexture;
	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _process(float delta);

		ObjectLoader();
	};
}
