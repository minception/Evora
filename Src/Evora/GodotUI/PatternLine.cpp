#include "PatternLine.h"
#include "GodotScenes.h"
#include <TextureRect.hpp>

using namespace godot;

void PatternLine::mouse_entered()
{
	int index = get("index");
	emit_signal("mouse_entered_pattern_line", index);
}

void PatternLine::mouse_exited()
{
	int index = get("index");
	cast_to<TextureRect>(get_node("Image"))->set_visible(false);
	emit_signal("mouse_exited_pattern_line", index);
}

void PatternLine::set_highlight(bool cond)
{
	cast_to<TextureRect>(get_node("Image"))->set_visible(cond);
}

void PatternLine::tile_moved(Vector2 position, int color)
{
	TextureRect* image = cast_to<TextureRect>(get_node("Image"));
	Vector2 pattern_line_size = image->get_size();
	Vector2 pattern_line_position = get_global_position();
	if(position.x > pattern_line_position.x
	&& position.x < pattern_line_position.x + pattern_line_size.x
	&& position.y > pattern_line_position.y
	&& position.y < pattern_line_position.y + pattern_line_size.y)
	{
		int index = get("index");
		emit_signal("tile_over", index, color);
	}
	else
	{
		set_highlight(false);
	}
}

void PatternLine::input()
{
	int index = get("index");
	emit_signal("mouse_entered_pattern_line", index);
}

bool PatternLine::is_mouse_over()
{
	Vector2 position = get_global_mouse_position();
	TextureRect* image = cast_to<TextureRect>(get_node("Image"));
	Vector2 pattern_line_size = image->get_size();
	Vector2 pattern_line_position = get_global_position();
	if (position.x > pattern_line_position.x
		&& position.x < pattern_line_position.x + pattern_line_size.x
		&& position.y > pattern_line_position.y
		&& position.y < pattern_line_position.y + pattern_line_size.y)
	{
		return true;
	}
	return false;
}

std::vector<Vector2> PatternLine::get_n_positions(int n)
{
	std::vector<Vector2> positions;
	TextureRect* image = cast_to<TextureRect>(get_node("Image"));
	Vector2 pattern_line_size = image->get_size();
	Vector2 pattern_line_position = get_global_position();
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	float margin = 5;
	for (int i = 0; i < n; ++i)
	{
		int xpos = pattern_line_position.x + pattern_line_size.x - (m_tile_count + i + 1) * tile_size.x - (m_tile_count + i) * margin;
		positions.push_back(Vector2(xpos, pattern_line_position.y));
	}
	m_tile_count += n;
	return positions;
}

void PatternLine::_register_methods()
{

	register_signal<PatternLine>("mouse_exited_pattern_line", "index", GODOT_VARIANT_TYPE_INT);
	register_signal<PatternLine>("mouse_entered_pattern_line", "index", GODOT_VARIANT_TYPE_INT);
	register_signal<PatternLine>("tile_over", "index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);

	register_method("mouse_entered", &PatternLine::mouse_entered);
	register_method("mouse_exited", &PatternLine::mouse_exited);
	register_method("tile_moved", &PatternLine::tile_moved);
	register_method("_ready", &PatternLine::_ready);
	register_method("input", &PatternLine::input);
	
	register_property("index", &PatternLine::set_index, &PatternLine::get_index, 0);
	register_property("tile_count", &PatternLine::m_tile_count, 0);
}

void PatternLine::_init()
{
	m_tile_count = 0;
}

void PatternLine::_ready()
{
	TextureRect* image = (TextureRect*)get_node("Image");
	image->connect("mouse_entered", this, "mouse_entered");
	image->connect("mouse_exited", this, "mouse_exited");
	image->connect("gui_input", this, "input");
}
