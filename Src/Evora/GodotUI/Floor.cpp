#include "Floor.h"
#include <TextureRect.hpp>
#include "GodotScenes.h"

using namespace godot;

void godot::Floor::_register_methods()
{
	register_property("tile_count", &Floor::m_tile_count, 0);

	register_method("tile_moved", &Floor::tile_moved);

	register_signal<Floor>("tile_over", "index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
}

void godot::Floor::_init()
{
}


bool Floor::is_mouse_over()
{
	Vector2 position = get_global_mouse_position();
	Control* image = cast_to<Control>(get_node("Image"));
	Vector2 floor_size = image->get_size();
	Vector2 floor_position = get_global_position();
	if (position.x > floor_position.x
		&& position.x < floor_position.x + floor_size.x
		&& position.y > floor_position.y
		&& position.y < floor_position.y + floor_size.y)
	{
		return true;
	}
	return false;
}

void Floor::set_highlight(bool cond)
{
	cast_to<TextureRect>(get_node("Image"))->set_visible(cond);
}


void Floor::tile_moved(Vector2 position, int color)
{
	Control* image = cast_to<Control>(get_node("Image"));
	Vector2 floor_size = image->get_size();
	Vector2 floor_position = get_global_position();
	if (position.x > floor_position.x
		&& position.x < floor_position.x + floor_size.x
		&& position.y > floor_position.y
		&& position.y < floor_position.y + floor_size.y)
	{
		emit_signal("tile_over", COLORS, color);
	}
	else
	{
		set_highlight(false);
	}
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
