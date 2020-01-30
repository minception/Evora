#include "Factory.h"
#include <TextureRect.hpp>
#include "Utils.h"
#include "GodotScenes.h"

using namespace godot;

void Factory::_register_methods()
{
}

void Factory::_init()
{
}

void Factory::add_tile(GodotTile* tile)
{
	tiles.push_back(tile);
}

Vector2 Factory::tile_position(int index)
{
	TextureRect* image = cast_to<TextureRect>(get_node("Image"));
	Vector2 factory_size = image->get_size();
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	int h_count = 2;
	int v_count = 2;
	float margin = 10.f;
	float h_space = (factory_size.x - 2 * margin - tile_size.x * h_count) / (h_count - 1);
	float v_space = (factory_size.y - 2 * margin - tile_size.y * v_count) / (v_count - 1);
	int column = index % h_count;
	int row = index / h_count;
	float posx = margin + (tile_size.x + h_space) * column;
	float posy = margin + (tile_size.y + v_space) * row;
	Vector2 local_pos(posx, posy);
	return get_global_position() + local_pos;
}
