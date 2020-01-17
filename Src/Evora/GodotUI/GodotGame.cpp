#include "GodotGame.h"
#include "ObjectLoader.h"

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

void GodotGame::draw(Vector2 viewport_size)
{
	// draw factories
	ObjectLoader::factory_loader->load_factories(factory_count(), Vector2(viewport_size.x / 2, 300), 200);
	// draw tiles in factories
	int factory_index(0);
	for(auto&& factory = factories_begin(); factory != factories_end(); factory++)
	{
		int index(0);
		for (auto&& tile : *factory)
		{
			ObjectLoader::tile_loader->add_tile(Vector2(35 * index + 50, 50*factory_index + 50), tile);
			++index;
		}
		++factory_index;
	}
	// draw boards
	ObjectLoader::board_loader->load_boards(player_count(), viewport_size);
}
