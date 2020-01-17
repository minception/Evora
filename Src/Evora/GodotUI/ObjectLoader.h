#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Resource.hpp>
#include <ResourceLoader.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include "Root.h"
#include <Texture.hpp>
#include "FactoryLoader.h"
#include "BoardLoader.h"
#include "TileLoader.h"

namespace godot
{
	class FactoryLoader;
	class BoardLoader;
	class TileLoader;
	class ObjectLoader
	{
	public:
		static FactoryLoader* factory_loader;
		static BoardLoader* board_loader;
		static TileLoader* tile_loader;

		ObjectLoader();
	};
}
