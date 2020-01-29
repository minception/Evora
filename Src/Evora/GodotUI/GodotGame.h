#pragma once
#include "game.h"
#include <Node2D.hpp>
#include <vector>

#include "ObjectLoader.h"
#include "Factory.h"

namespace godot
{
	class ObjectLoader;
	using namespace model;
	class GodotGame : public game
	{
		std::vector<godot::Node2D> m_tiles;
		std::vector<Factory*> m_factories_display;
	public:
		void draw(Vector2 viewport_size);
		GodotGame(int players) :game(players) {}
	};
}
