#include "GodotGame.h"
#include "ObjectLoader.h"
#include "GodotScenes.h"
#include <core/Godot.hpp>
#include "Center.h"
#include "PatternLine.h"
#include "Floor.h"

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
		GodotScenes::game_data->players[GodotScenes::game_data->current_player]->move();
	}
	return added;
}

int GodotGame::factory_to_pattern_line(int factory_index, int player_index, int pattern_line_index, tile color)
{
	//_ASSERT(false);
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
			godot_tile->set("pattern_line_index", pattern_line_index);
			godot_tile->set("board_index", player_index);
			godot_tile->animate_to(positions[positionIndex++]);
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
			godot_tile->set("board_index", player_index);
			godot_tile->set("pattern_line_index", COLORS);
			godot_tile->animate_to(positions[positionIndex++]);
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
			godot_tile->set("factory_index", -1);
			godot_tile->animate_to(Vector2(tile_position.x, tile_position.y + 1000));
			// ObjectLoader::tile_loader->remove_child(godot_tile);
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

bool GodotGame::handle_starter_tile(int player_index)
{
	if (game::handle_starter_tile(player_index))
	{
		Center* center = (Center*)GodotScenes::root->get_node("Center");
		GodotTile* starter_tile = (GodotTile*)GodotScenes::root->get_node("StarterTile");
		Vector2 position = center->get_n_positions(1)[0];
		starter_tile->animate_to(position);
		return true;
	}
	return false;
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
			godot_tile->set("board_index", player_index);
			godot_tile->set("pattern_line_index", pattern_line_index);
			godot_tile->animate_to(positions[positionIndex++]);
		}
	}
	center->take_n_tiles(count);
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
			godot_tile->set("board_index", player_index);
			godot_tile->set("pattern_line_index", COLORS);
			godot_tile->animate_to(positions[positionIndex++]);
		}
	}
	center->take_n_tiles(count);
	return count;
}

int GodotGame::center_to_lid(tile color)
{
	int count = game::center_to_lid(color);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	for (int i = 0; i < tile_count; ++i)
	{
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		tile tile_color = (tile)(int)godot_tile->get("color");

		if (tile_factory_index == factory_count() && tile_color == color)
		{
			godot_tile->set_follow(false);
			Vector2 tile_position = godot_tile->get_global_position();
			godot_tile->set("factory_index", -1);
			godot_tile->animate_to(Vector2(tile_position.x, tile_position.y + 1000));
			// ObjectLoader::tile_loader->remove_child(godot_tile);
		}
	}
	Center* center = (Center*)GodotScenes::root->get_node("Center");
	center->take_n_tiles(count);
	std::vector<Vector2> positions = center->get_rearrange_positions();
	int position_index = 0;
	for (int i = 0; i < tile_count; ++i)
	{
		if (position_index == positions.size()) break;
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_factory_index = godot_tile->get("factory_index");
		if (tile_factory_index == factory_count())
		{
			godot_tile->animate_to(positions[position_index++]);
		}
	}
	return count;
}

bool GodotGame::handle_center_starter_tile(int player_index)
{
	if(game::handle_center_starter_tile(player_index))
	{
		Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
		GodotTile* starter_tile = (GodotTile*)GodotScenes::root->get_node("StarterTile");
		Vector2 position = board->get_floor_positions(1)[0];
		starter_tile->animate_to(position);
		Center* center = (Center*)GodotScenes::root->get_node("Center");
		center->take_n_tiles(1);
		return true;
	}
	return false;
}

void godot::GodotGame::starter_tile_unhandled()
{
	game::starter_tile_unhandled();
	GodotTile* starter_tile = (GodotTile*)GodotScenes::root->get_node("StarterTile");
	int starter_player_index = game::get_first_player();
	GodotScenes::game_data->current_player = starter_player_index;
	Board* board = (Board*)ObjectLoader::board_loader->get_child(starter_player_index);
	Vector2 position = board->get_starter_tile_position();
	starter_tile->animate_to(position);
}

tile GodotGame::tile_wall(int player_index, int pattern_line_index)
{
	tile color = game::tile_wall(player_index, pattern_line_index);
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	bool transfered = false;
	for (int i = 0; i < tile_count; ++i)
	{
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_board_index = godot_tile->get("board_index");
		int tile_pattern_line_index = godot_tile->get("pattern_line_index");
		Vector2 wall_position = board->get_wall_position(pattern_line_index, (int)color);
		if (player_index == tile_board_index && tile_pattern_line_index == pattern_line_index)
		{
			godot_tile->set("pattern_line_index", -1);
			if(!transfered)
			{
				godot_tile->animate_to(wall_position);
				transfered = true;
				continue;
			}
			Vector2 tile_position = godot_tile->get_global_position();
			godot_tile->animate_to(Vector2(tile_position.x, tile_position.y + 1000));
			// ObjectLoader::tile_loader->remove_child(godot_tile);
		}
	}
	PatternLine* pattern_line = (PatternLine*)board->get_node("Image/PatternLines")->get_child(pattern_line_index);
	pattern_line->set("tile_count", 0);
	return color;
}

int GodotGame::score_wall_tile(int player_index, int pattern_line_index, tile tile)
{
	int score = game::score_wall_tile(player_index, pattern_line_index, tile);
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	std::vector<int> score_indices = get_score_indices(player_index, pattern_line_index, tile);
	board->display_wall_tile_score(score_indices, pattern_line_index, (int)tile, score);
	return score;
}

int GodotGame::score_floor(int player_index)
{
	int score = game::score_floor(player_index);
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	board->display_floor_score(score);
	return score;
}

int GodotGame::floor_to_lid(int player_index)
{
	int count = game::floor_to_lid(player_index);
	Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
	int tile_count = ObjectLoader::tile_loader->get_child_count();
	for (int i = 0; i < tile_count; ++i)
	{
		GodotTile* godot_tile = (GodotTile*)ObjectLoader::tile_loader->get_child(i);
		int tile_board_index = godot_tile->get("board_index");
		int tile_pattern_line_index = godot_tile->get("pattern_line_index");
		if (player_index == tile_board_index && tile_pattern_line_index == COLORS)
		{
			godot_tile->set("pattern_line_index", -1);
			Vector2 tile_position = godot_tile->get_global_position();
			godot_tile->animate_to(Vector2(tile_position.x, tile_position.y + 1000));
			// ObjectLoader::tile_loader->remove_child(godot_tile);
		}
	}
	Floor* floor = (Floor*)ObjectLoader::board_loader->get_child(player_index)->get_node("Image/Floor");
	floor->set("tile_count", 0);
	// when the floor is empty, no animation occurs, this only serves to move to the next step
	if (count == 0) GodotScenes::root->animation_finished();
	return count;
}

int GodotGame::score_wall_color(int player_index, tile color)
{
	int score = game::score_wall_color(player_index, color);
	if(score > 0)
	{
		Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
		board->display_wall_color_score((int)color, score);
	}
	else
	{
		GodotScenes::game_data->controller->step();
	}
	return score;
}

int GodotGame::score_wall_line(int player_index, int line)
{
	int score = game::score_wall_line(player_index, line);
	if (score > 0)
	{
		Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
		board->display_wall_line_score(line, score);
	}
	else
	{
		GodotScenes::game_data->controller->step();
	}
	return score;
}

int GodotGame::score_wall_row(int player_index, int row)
{
	int score = game::score_wall_row(player_index, row);
	if (score > 0)
	{
		Board* board = (Board*)ObjectLoader::board_loader->get_child(player_index);
		board->display_wall_row_score(row, score);
	}
	else
	{
		GodotScenes::game_data->controller->step();
	}
	return score;
}
