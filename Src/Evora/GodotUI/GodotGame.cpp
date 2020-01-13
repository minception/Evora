#include "GodotGame.h"

using namespace godot;

bool godot::GodotGame::factory_offer(int player, int factory, tile color, int line)
{
	return game::factory_offer(player, factory, color, line);
}

bool godot::GodotGame::center_offer(int player, tile color, int line)
{
	return game::center_offer(player, color, line);
}

bool godot::GodotGame::tile_walls()
{
	return game::tile_walls();
}

void GodotGame::draw(ObjectLoader* loader)
{
	// draw factories
	for (auto&& factory = factories_begin(); factory!= factories_end(); ++factory)
	{
		
	}
	// draw boards
	for(auto&& board = players_begin(); board != players_end(); ++board)
	{
		
	}
}
