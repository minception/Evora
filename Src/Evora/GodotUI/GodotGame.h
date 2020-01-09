#pragma once
#include "game.h"
#include "ObjectLoader.h"
#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <vector>

namespace godot
{
	using namespace model;
	class GodotGame: public game
	{
		std::vector<Node2D> m_tiles;
		
	public:
		bool factory_offer(int player, int factory, tile color, int line) override;
		bool center_offer(int player, tile color, int line) override;
		bool tile_walls() override;
		void draw(ObjectLoader loader);
	};
}
