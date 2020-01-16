#pragma once

#include <core/Godot.hpp>
#include <memory>
#include <Node2D.hpp>

#include "BoardLoader.h"
#include "FactoryLoader.h"
#include "GodotGame.h"
#include "TileLoader.h"

namespace godot
{
	class GodotGame;
	class BoardLoader;
	class FactoryLoader;
	class TileLoader;
	class Root :public Node2D
	{
		GODOT_CLASS(Root, Node2D)
		std::shared_ptr<GodotGame> m_game;
	public:
		//static ObjectLoader* p_loader;
		static BoardLoader* p_board_loader;
		static FactoryLoader* p_factory_loader;
		static TileLoader* p_tile_loader;
		static void _register_methods();
		void _init();
		void _ready();

		Root() { m_game = std::make_shared<GodotGame>(2); }
	};
}
