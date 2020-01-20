#pragma once
#include "game.h"
#include <Node2D.hpp>
#include <vector>

#include "ObjectLoader.h"

namespace godot
{
	class ObjectLoader;
	using namespace model;
	class GodotGame : public game
	{
		std::vector<godot::Node2D> m_tiles;
		std::vector<Factory*> m_factories_display;
	public:
		bool factory_offer(int player, int factory, tile color, int line) override;
		bool center_offer(int player, tile color, int line) override;
		bool tile_walls() override;
		void draw(Vector2 viewport_size);
		GodotGame(int players) :game(players) {}
	};
}
