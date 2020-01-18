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
	class Root :public Node2D
	{
		GODOT_CLASS(Root, Node2D)
		std::shared_ptr<GodotGame> m_game;
	public:
		static void _register_methods();
		void _init();
		void _ready();

		Root() { m_game = std::make_shared<GodotGame>(3); }
	};
}
