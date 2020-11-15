#include "Center.h"
#include "GodotScenes.h"

void godot::Center::_register_methods()
{
	register_property("tile_count", &Center::m_tile_count, 0);
}

void godot::Center::_init()
{
	m_tiles_per_line = 5;
	m_tile_count = 0;
}

std::vector<godot::Vector2> godot::Center::get_n_positions(int n)
{
	std::vector<Vector2> positions;
	Vector2 center_position = get_global_position();
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	float margin = 5.f;
	int tile_count = get("tile_count");
	for (int i = 0; i < n; ++i)
	{
		int line = (tile_count + i) / 5;
		int row = (tile_count + i) % 5;
		float xpos = center_position.x + (tile_size.x + margin) * row;
		float ypos = center_position.y + (tile_size.y + margin) * line;
		positions.push_back(Vector2(xpos, ypos));
	}
	set("tile_count", tile_count + n);
	return positions;
}

std::vector<Vector2> Center::get_rearrange_positions()
{
	std::vector<Vector2> positions;
	Control* image = cast_to<Control>(get_node("Image"));
	Vector2 center_position = get_global_position();
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	float margin = 5.f;
	int tile_count = get("tile_count");
	for (int i = 0; i < tile_count; ++i)
	{
		int line = i / 5;
		int row = i % 5;
		float xpos = center_position.x + (tile_size.x + margin) * row;
		float ypos = center_position.y + (tile_size.y + margin) * line;
		positions.push_back(Vector2(xpos, ypos));
	}
	return positions;
}

void Center::take_n_tiles(int n)
{
	int tile_count = get("tile_count");
	set("tile_count", tile_count - n);
}
