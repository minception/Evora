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
	class TileLoader :public KinematicBody2D
	{
		GODOT_CLASS(TileLoader, KinematicBody2D)
	private:
		Ref<PackedScene> tileScene;
		Ref<Texture> blackTexture;
		Ref<Texture> whiteTexture;
		Ref<Texture> blueTexture;
		Ref<Texture> redTexture;
		Ref<Texture> yellowTexture;
	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _process(float delta);

		TileLoader();
	};
}
