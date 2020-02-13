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
		bool wait_for_refill;
	public:
		GodotGame(int players) :game(players) {}
		int bag_to_factories() override;
		int factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color) override;
		int factory_to_floor(int factory_index, int player_index, tile color) override;
		int factory_to_lid(int factory_index, tile color) override;
		int factory_to_center(int factory_index) override;
		bool handle_starter_tile(int player_index) override;
		int center_to_pattern_line(int player_index, int pattern_line_index, tile color) override;
		int center_to_floor(int player_index, tile color) override;
		int center_to_lid(tile color) override;
		bool handle_center_starter_tile(int player_index) override;
		void starter_tile_unhandled() override;
		tile tile_wall(int player_index, int pattern_line_index) override;
		int score_wall_tile(int player_index, int pattern_line_index, tile tile) override;
	};
}
