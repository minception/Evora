#include "Center.h"
#include "GodotScenes.h"

void godot::Center::_register_methods()
{
}

void godot::Center::_init()
{
	m_tiles_per_line = 5;
}

std::vector<godot::Vector2> godot::Center::get_n_positions(int n)
{
	std::vector<Vector2> positions;
	Control* image = cast_to<TextureRect>(get_node("Image"));
	Vector2 center_position = get_global_position();
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	float margin = 5;
	for (int i = 0; i < n; ++i)
	{
		int line = (m_tile_count + i) / 5;
		int row = (m_tile_count + i) % 5;
		int xpos = center_position.x + (tile_size.x + margin) * row;
		int ypos = center_position.y + (tile_size.y + margin) * line;
		positions.push_back(Vector2(xpos, ypos));
	}
	m_tile_count += n;
	return positions;
}
