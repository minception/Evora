#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>

#include <memory>

#include "GodotGame.h"

namespace godot
{
	class GodotGame;
	class Root :public Node2D
	{
		GODOT_CLASS(Root, Node2D)
		std::shared_ptr<GodotGame> m_game;
	public:
		//static ObjectLoader* p_loader;
		static void _register_methods();
		void _init();

		Root() { m_game = std::make_shared<GodotGame>(2); }
	};
}
