#include "GodotTile.h"
#include <Node2D.hpp>
#include <Label.hpp>
#include <string>
#include <Sprite.hpp>

using namespace godot;

bool GodotTile::_holding_one = false;

void GodotTile::_register_methods()
{
	register_method("_process", &GodotTile::_process);
	register_method("_on_mouse_entered", &GodotTile::_on_mouse_entered);
	register_method("_on_mouse_exited", &GodotTile::_on_mouse_exited);
	register_method("_area_input_event", &GodotTile::_area_input_event);
}

void GodotTile::_init()
{
	_label = (Label*)get_child(1);
	_input = Input::get_singleton();
}

void GodotTile::_process(float delta)
{
	if(_holding)
	{
		Vector2 mouse_position = get_global_mouse_position();
		Vector2 viewport_size = get_viewport_rect().size;
		if(mouse_position.x > 0 && mouse_position.y > 0 &&
			mouse_position.x < viewport_size.x && mouse_position.y < viewport_size.y)
			set_global_position(get_global_mouse_position());
	}
	if(_moving_back)
	{
		Vector2 shift = get_global_position() - _original_position;
		if(shift.length() < 1.f)
		{
			set_global_position(_original_position);
			_moving_back = false;
		}
		Vector2 speed = shift * delta * 10;
		set_global_position(get_global_position() - speed);
	}
}

void GodotTile::_on_mouse_entered()
{
	++_enter_count;
	Label* label = (Label*)get_child(1);
	label->set_text(String(std::to_string(_enter_count).c_str()));

	Sprite* highlight = (Sprite*)get_child(2);
	highlight->set_visible(true);
}

void GodotTile::_on_mouse_exited()
{
	Sprite* highlight = (Sprite*)get_child(2);
	highlight->set_visible(false);
}

void GodotTile::_area_input_event()
{
	int64_t mouse_button_mask = _input->get_mouse_button_mask();
	if(mouse_button_mask & 1) // left mouse button pressed
	{
		if (_holding_one) return;
		_holding = true;
		_original_position = get_global_position();
		_holding_one = true;
	}
	else if(_holding)
	{
		_holding = false;
		_moving_back = true;
		_holding_one = false;
		
	}
	
}


GodotTile::GodotTile()
{
}
