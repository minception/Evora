#include "GodotTile.h"
#include <Node2D.hpp>
#include <Label.hpp>
#include <string>
#include <Sprite.hpp>
#include "Utils.h"
#include "tile.h"

#include <ResourceLoader.hpp>

using namespace godot;

bool GodotTile::_holding_one = false;

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

void GodotTile::_register_methods()
{
	register_method("_process", &GodotTile::_process);
	register_method("_ready", &GodotTile::_ready);
	register_method("_on_mouse_entered", &GodotTile::_on_mouse_entered);
	register_method("_on_mouse_exited", &GodotTile::_on_mouse_exited);
	register_method("_area_input_event", &GodotTile::_area_input_event);

	register_property("color", &GodotTile::set_color,&GodotTile::get_color, 0);
	register_property("index", &GodotTile::_index, 0);
	register_property("factory_index", &GodotTile::_factory_index, 0);
	register_property("holding", &GodotTile::_holding, false);
	register_property("original_position", &GodotTile::_original_position, Vector2(0, 0));
	
	register_signal<GodotTile>("mouse_entered", "factory_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<GodotTile>("picked_up", "factory_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
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
	int image_index = get_child_index(this, "Image");
	_image = (TextureRect*)get_child(image_index);
	
	_label = (Label*)_image->get_child(get_child_index(_image, "Text"));
	_highlight = (TextureRect*)_image->get_child(get_child_index(_image, "Highlight"));
	_input = Input::get_singleton();
}

void GodotTile::_process(float delta)
{
	if(get("holding"))
	{
		Vector2 mouse_position = get_global_mouse_position();
		Vector2 viewport_size = get_viewport_rect().size;
		if(mouse_position.x > 0 && mouse_position.y > 0 &&
			mouse_position.x < viewport_size.x && mouse_position.y < viewport_size.y)
			set_global_position(get_global_mouse_position());
	}
	if(_moving_back)
	{
		Vector2 shift = get_global_position() - get("original_position");
		if(shift.length() < 1.f)
		{
			set_global_position(get("original_position"));
			_moving_back = false;
		}
		Vector2 speed = shift * delta * 10;
		set_global_position(get_global_position() - speed);
	}
}

void GodotTile::_on_mouse_entered()
{
	_highlight->set_visible(true);
	emit_signal("mouse_entered", _factory_index, _color);
}

void GodotTile::_on_mouse_exited()
{
	_highlight->set_visible(false);
}

void GodotTile::_area_input_event()
{
	if (_moving_back) return; // no input when animating
	int64_t mouse_button_mask = _input->get_mouse_button_mask();
	if(mouse_button_mask & 1) // left mouse button pressed
	{
		if (_holding_one) return;
		emit_signal("picked_up", _factory_index, _color);
	}
	else if(get("holding"))
	{
		set("holding", false);
		_moving_back = true;
		_holding_one = false;
		
	}
	
}

bool GodotTile::pick_up(int factory, int color)
{
	_factory_index = get("factory_index");
	_color = get("color");
	if(_factory_index == factory && _color == color)
	{
		set("holding", true);
		set("original_position", get_global_position());
		return true;
	}
	return false;
}
