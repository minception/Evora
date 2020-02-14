#include "GodotTile.h"
#include <Node2D.hpp>
#include <Label.hpp>
#include <string>
#include <Sprite.hpp>
#include "Utils.h"
#include "tile.h"

#include <ResourceLoader.hpp>

using namespace godot;

Ref<Texture> GodotTile::blackTexture;
Ref<Texture> GodotTile::whiteTexture;
Ref<Texture> GodotTile::blueTexture;
Ref<Texture> GodotTile::redTexture;
Ref<Texture> GodotTile::yellowTexture;
Ref<Texture> GodotTile::starterTexture;

void GodotTile::set_color(int color)
{
	_color = color;
	TextureRect* image = (TextureRect*)get_child(get_child_index(this, "Image"));
	switch ((model::tile)color)
	{
	case model::tile::black:
		image->set_texture(blackTexture);
		break;
	case model::tile::blue:
		image->set_texture(blueTexture);
		break;
	case model::tile::red:
		image->set_texture(redTexture);
		break;
	case model::tile::white:
		image->set_texture(whiteTexture);
		break;
	case model::tile::yellow:
		image->set_texture(yellowTexture);
		break;
	case model::tile::starter:
		image->set_texture(starterTexture);
		break;
	case model::tile::empty:
		image->set_texture(nullptr);
		break;
	}
}

int GodotTile::get_color()
{
	return _color;
}

void GodotTile::set_interactive(bool cond)
{
	_interactive = cond;
}

bool GodotTile::get_interactive()
{
	return _interactive;
}

void GodotTile::set_pattern_line_index(int value)
{
	_pattern_line_index = value;
	set("interactive", false);
}

int GodotTile::get_pattern_line_index()
{
	return _pattern_line_index;
}

void GodotTile::_register_methods()
{
	register_method("_process", &GodotTile::_process);
	register_method("_ready", &GodotTile::_ready);
	register_method("_on_mouse_entered", &GodotTile::_on_mouse_entered);
	register_method("_on_mouse_exited", &GodotTile::_on_mouse_exited);
	register_method("_area_input_event", &GodotTile::_area_input_event);

	register_property("color", &GodotTile::set_color,&GodotTile::get_color, 0);
	register_property("factory_index", &GodotTile::_factory_index, 0);
	register_property("interactive", &GodotTile::set_interactive, &GodotTile::get_interactive, false);
	register_property("follow_mouse", &GodotTile::m_follow_mouse, false);
	register_property("original_position", &GodotTile::m_original_position, Vector2(0, 0));
	register_property("move_back", &GodotTile::m_move_back, false);
	register_property("animating", &GodotTile::m_animating, false);
	register_property("animating_to", &GodotTile::m_animating_to, Vector2(0, 0));
	register_property("pattern_line_index", &GodotTile::set_pattern_line_index, &GodotTile::get_pattern_line_index, -1);
	register_property("board_index", &GodotTile::_board_index, -1);
	
	register_signal<GodotTile>("mouse_entered", "factory_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<GodotTile>("mouse_exited", "factory_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<GodotTile>("selected", "factory_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<GodotTile>("following", "factory_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<GodotTile>("dropped", "factory_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<GodotTile>("tile_moved", "position", GODOT_VARIANT_TYPE_VECTOR2, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<GodotTile>("animation_started", Dictionary());
	register_signal<GodotTile>("animation_finished", Dictionary());
}

void GodotTile::_init()
{
	ResourceLoader* rl = ResourceLoader::get_singleton();
	blackTexture = rl->load("res://Textures/black-tile.png");
	whiteTexture = rl->load("res://Textures/white-tile.png");
	blueTexture = rl->load("res://Textures/blue-tile.png");
	redTexture = rl->load("res://Textures/red-tile.png");
	yellowTexture = rl->load("res://Textures/yellow-tile.png");
	starterTexture = rl->load("res://Textures/starter-tile.png");
}

void GodotTile::_ready()
{
	_image = cast_to<TextureRect>(get_node("Image"));
	
	_label = cast_to<Label>(_image->get_node("Text"));
	_highlight = cast_to<TextureRect>(_image->get_node("Highlight"));
	_input = Input::get_singleton();
	
}

void GodotTile::_process(float delta)
{
	if(m_animating)
	{
		Vector2 target_location = m_animating_to;
		Vector2 starting_location = get_global_position();
		Vector2 speed = target_location - starting_location;
		if (speed.length() < 3)
		{
			set_global_position(target_location);
			m_animating = false;
			emit_signal("animation_finished");
		}
		else
		{
			set_global_position(starting_location + speed * delta * 10);
		}
		return;
	}
	if(m_move_back)
	{
		Vector2 target_location = m_original_position;
		Vector2 starting_location = get_global_position();
		Vector2 speed = target_location - starting_location;
		if (speed.length() < 3)
		{
			set_global_position(target_location);
			m_move_back = false;
			_interactive = true;
			set_z_index(0);
		}
		else
		{
			set_global_position(starting_location + speed * delta * 10);
		}
		return;
	}
	if(m_follow_mouse)
	{
		Vector2 target_location = get_global_mouse_position() - _image->get_size() / 2;
		Vector2 starting_location = get_global_position();
		Vector2 speed = target_location - starting_location;
		if(speed.length() < 3)
		{
			set_global_position(target_location);
		}
		else
		{
			set_global_position(starting_location + speed * delta * 20);
		}
		emit_signal("tile_moved", get_global_mouse_position(), _color);
	}
}

void GodotTile::_on_mouse_entered()
{
	if(_interactive)
		emit_signal("mouse_entered", _factory_index, _color);
}

void GodotTile::_on_mouse_exited()
{
	emit_signal("mouse_exited", _factory_index, _color);
}

void GodotTile::_area_input_event()
{
	int64_t mouse_button_mask = _input->get_mouse_button_mask();
	if(m_follow_mouse)
	{
		if(!(mouse_button_mask&1))
		{
			emit_signal("dropped", _factory_index, _color);
		}
		return;
	}
	if (!_interactive) return;
	if (mouse_button_mask & 1)
	{
		Vector2 mouse_position = get_global_mouse_position();
		if(m_clicked)
		{
			if(m_clicked_on.distance_to(mouse_position) > 0)
			{
				emit_signal("following", _factory_index, _color);
			}
		}
		else
		{
			m_clicked = true;
			m_clicked_on = mouse_position;
		}
	}
	else
	{
		if(m_clicked)
		{
			emit_signal("selected", _factory_index, _color);
			m_clicked = false;
		}
	}
}



void GodotTile::set_select(bool cond)
{
	TextureRect* highlight = cast_to<TextureRect>(get_node("Image/Highlight"));
	highlight->set_visible(cond);
}

void GodotTile::set_highlight(bool cond)
{
	TextureRect* highlight = cast_to<TextureRect>(get_node("Image/Highlight"));
	highlight->set_visible(cond);
}

void GodotTile::set_follow(bool cond)
{
	if (cond)
	{
		set("original_position", get_global_position());
		set_z_index(5);
	}
	set("follow_mouse", cond);
}

void GodotTile::set_move_back(bool cond)
{
	set("move_back", cond);
}

void GodotTile::animate_to(Vector2 position)
{
	set("animating", true);
	set("animating_to", position);
	emit_signal("animation_started");
}

