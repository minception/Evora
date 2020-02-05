#include "Floor.h"
#include <TextureRect.hpp>
#include "GodotScenes.h"

using namespace godot;

void godot::Floor::_register_methods()
{
	register_property("tile_count", &Floor::m_tile_count, 0);
}

void godot::Floor::_init()
{
}

std::vector<Vector2> Floor::get_n_positions(int n)
{

	std::vector<Vector2> positions;
	Control* area = cast_to<Control>(get_node("Image"));
	Vector2 floor_size = area->get_size();
	Vector2 floor_position = get_global_position();
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	int tile_count = get("tile_count");
	float margin = 5;
	for (int i = 0; i < n; ++i)
	{
		int xpos = floor_position.x + (tile_count + i) * tile_size.x + (tile_count + i) * margin;
		positions.push_back(Vector2(xpos, floor_position.y));
	}
	tile_count += n;
	set("tile_count", tile_count);
	return positions;
}
