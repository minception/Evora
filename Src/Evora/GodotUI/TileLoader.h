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
		static Ref<PackedScene> tileScene;
		static Ref<Texture> blackTexture;
		static Ref<Texture> whiteTexture;
		static Ref<Texture> blueTexture;
		static Ref<Texture> redTexture;
		static Ref<Texture> yellowTexture;
	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _process(float delta);

		TileLoader();
	};
}
