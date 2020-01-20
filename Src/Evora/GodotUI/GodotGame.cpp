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
	m_factories_display = ObjectLoader::factory_loader->load_factories(factory_count(), Vector2(viewport_size.x / 2, 300), 200);
	// draw tiles in factories
	auto&& factory = factories_begin();
	for(int i = 0; i<factory_count(); ++i)
	{
		int index(0);
		for (auto&& tile : *factory)
		{
			// TODO: get real tile size here
			ObjectLoader::tile_loader->add_tile(m_factories_display[i]->tile_position(index, Vector2(32,32)), tile);
			++index;
		}
		++factory;
	}
	// draw boards
	ObjectLoader::board_loader->load_boards(player_count(), viewport_size);
}
