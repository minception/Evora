#include "GodotGame.h"
#include "ObjectLoader.h"
#include "GodotScenes.h"
#include <core/Godot.hpp>
#include "Center.h"

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

int GodotGame::factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color)
{
	int count = game::factory_to_pattern_line(factory_index, player_index, pattern_line_index, color);
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	std::vector<Vector2> positions = board->get_pattern_line_positions(pattern_line_index, count);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	int positionIndex = 0;
	for (int i = 0; i < tile_count; ++i)
	{
		if (positionIndex == positions.size()) break;
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		tile tile_color = (tile)(int)godot_tile->get("color");

		if (tile_factory_index == factory_index && tile_color == color)
		{
			godot_tile->set_follow(false);
			godot_tile->set("factory_index", -1);
			godot_tile->animate_to(positions[positionIndex++]);
			// factory index of tiles in center is one bigger than a biggest factory index
			int center_index = factory_count();
			godot_tile->set("factory_index", center_index);
		}
	}
	return count;
}

int GodotGame::factory_to_floor(int factory_index, int player_index, tile color)
{
	int count = game::factory_to_floor(factory_index, player_index, color);
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	std::vector<Vector2> positions = board->get_floor_positions(count);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	int positionIndex = 0;
	for (int i = 0; i < tile_count; ++i)
	{
		if (positionIndex == positions.size()) break;
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		tile tile_color = (tile)(int)godot_tile->get("color");

		if (tile_factory_index == factory_index && tile_color == color)
		{
			godot_tile->set_follow(false);
			godot_tile->set("factory_index", -1);
			godot_tile->animate_to(positions[positionIndex++]);
			// factory index of tiles in center is one bigger than a biggest factory index
			int center_index = factory_count();
			godot_tile->set("factory_index", center_index);
		}
	}
	return count;
}

int GodotGame::factory_to_lid(int factory_index, tile color)
{
	int count = game::factory_to_lid(factory_index, color);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	for (int i = 0; i < tile_count; ++i)
	{
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		tile tile_color = (tile)(int)godot_tile->get("color");
		
		if (tile_factory_index == factory_index && tile_color == color)
		{
			godot_tile->set_follow(false);
			Vector2 tile_position = godot_tile->get_global_position();
			godot_tile->animate_to(Vector2(tile_position.x, tile_position.y - 1000));
			ObjectLoader::tile_loader->remove_child(godot_tile);
		}
	}
	return count;
}

int GodotGame::factory_to_center(int factory_index)
{
	int count = game::factory_to_center(factory_index);
	Center* center = (Center*)GodotScenes::root->get_node("Center");
	std::vector<Vector2> positions = center->get_n_positions(count);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	int positionIndex = 0;
	for (int i = 0; i < tile_count; ++i)
	{
		if (positionIndex == positions.size()) break;
		GodotTile* tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = tile->get("factory_index");
		if(tile_factory_index == factory_index)
		{
			tile->set_follow(false);
			tile->animate_to(positions[positionIndex++]);
			// factory index of tiles in center is one bigger than a biggest factory index
			int center_index = factory_count();
			tile->set("factory_index", center_index);
		}
	}
	return count;
}

int GodotGame::center_to_pattern_line(int player_index, int pattern_line_index, tile color)
{
	int count = game::center_to_pattern_line(player_index, pattern_line_index, color);
	Center* center = (Center*)GodotScenes::root->get_node("Center");
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	std::vector<Vector2> positions = board->get_pattern_line_positions(pattern_line_index, count);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	int positionIndex = 0;
	for (int i = 0; i < tile_count; ++i)
	{
		if (positionIndex == positions.size()) break;
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		tile tile_color = (tile)(int)godot_tile->get("color");

		if (tile_factory_index == factory_count() && tile_color == color)
		{
			godot_tile->set_follow(false);
			godot_tile->set("factory_index", -1);
			godot_tile->animate_to(positions[positionIndex++]);
			// factory index of tiles in center is one bigger than a biggest factory index
			int center_index = factory_count();
			godot_tile->set("factory_index", center_index);
		}
	}
	return count;
}

int GodotGame::center_to_floor(int player_index, tile color)
{
	int count = game::center_to_floor(player_index, color);
	Center* center = (Center*)GodotScenes::root->get_node("Center");
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	std::vector<Vector2> positions = board->get_floor_positions(count);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	int positionIndex = 0;
	for (int i = 0; i < tile_count; ++i)
	{
		if (positionIndex == positions.size()) break;
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		tile tile_color = (tile)(int)godot_tile->get("color");

		if (tile_factory_index == factory_count() && tile_color == color)
		{
			godot_tile->set_follow(false);
			godot_tile->set("factory_index", -1);
			godot_tile->animate_to(positions[positionIndex++]);
			// factory index of tiles in center is one bigger than a biggest factory index
			int center_index = factory_count();
			godot_tile->set("factory_index", center_index);
		}
	}
	return count;
}

int GodotGame::center_to_lid(tile color)
{
	int count = game::center_to_lid(color);
	if (count == 0) return count;
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	for (int i = 0; i < tile_count; ++i)
	{
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		tile tile_color = (tile)(int)godot_tile->get("color");

		if (tile_factory_index == factory_count() && tile_color == color)
		{
			Vector2 tile_position = godot_tile->get_global_position();
			godot_tile->animate_to(Vector2(tile_position.x, tile_position.y - 1000));
			ObjectLoader::tile_loader->remove_child(godot_tile);
		}
	}
	return count;
}

bool GodotGame::handle_center_starter_tile(int player_index)
{
	if(game::handle_center_starter_tile(player_index))
	{
		return true;
	}
	return false;
}

tile GodotGame::tile_wall(int player_index, int pattern_line_index)
{
	tile color = game::tile_wall(player_index, pattern_line_index);
	return color;
}

int GodotGame::score_wall_tile(int player_index, int pattern_line_index, tile tile)
{
	int score = game::score_wall_tile(player_index, pattern_line_index, tile);
	return score;
}
