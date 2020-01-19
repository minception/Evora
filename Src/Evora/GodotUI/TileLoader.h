#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include "Root.h"
#include <Texture.hpp>
#include "tile.h"

namespace godot
{
	class TileLoader :public Node2D
	{
		GODOT_CLASS(TileLoader, Node2D)
	private:
		static Ref<PackedScene> tileScene;
		static Ref<Texture> blackTexture;
		static Ref<Texture> whiteTexture;
		static Ref<Texture> blueTexture;
		static Ref<Texture> redTexture;
		static Ref<Texture> yellowTexture;
		static Ref<Texture> starterTexture;
	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _process(float delta);
		void add_tile(Vector2 position, model::tile color);

		TileLoader();
	};
}
