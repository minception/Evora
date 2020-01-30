#include "GodotGame.h"
#include "ObjectLoader.h"
#include "GodotScenes.h"
#include "Utils.h"

using namespace godot;

int GodotGame::bag_to_factories()
{
	int added = game::bag_to_factories();
	if (!wait_for_refill && added < factory_count() * factory::TILES)
	{
		wait_for_refill = true;
	}
	else
	{
		int factory_index = 0;
		for(auto&& factory= factories_begin(); factory!= factories_end(); ++factory)
		{
			int tile_index = 0;
			for(auto&& tile:(*factory))
			{
				int factories_count = ObjectLoader::factory_loader->get_child_count();
				Factory* factory_display = (Factory*)ObjectLoader::factory_loader->get_child(factory_index);
				ObjectLoader::tile_loader->add_tile(factory_display->tile_position(tile_index), tile, factory_index);
				++tile_index;
			}
			++factory_index;
		}
		wait_for_refill = false;
	}
	return added;
}
