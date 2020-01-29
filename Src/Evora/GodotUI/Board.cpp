#include "Board.h"
#include "Utils.h"
#include <TextureRect.hpp>
#include <Control.hpp>
#include <Input.hpp>

using namespace godot;

void Board::set_highlight(bool cond)
{
	TextureRect* image = (TextureRect*)get_child(get_child_index(this, "Image"));
	TextureRect* highlight = (TextureRect*)image->get_child(get_child_index(image, "Highlight"));
	highlight->set_visible(cond);
}

void Board::_register_methods() {
	register_method("_process", &Board::_process);
	register_method("_ready", &Board::_ready);

	register_method("mouse_entered", &Board::mouse_entered);
	register_method("mouse_exited", &Board::mouse_exited);
	register_method("image_input", &Board::image_input);

	register_property("index", &Board::index, 0);
	register_property("player_select", &Board::player_select, false);

	register_signal<Board>("selected", "index", GODOT_VARIANT_TYPE_INT);
}

void godot::Board::_init()
{
	
}

void godot::Board::_process(float delta)
{
}

void Board::connect_children()
{
	// I had to put this here, because children kept stealing focus from the board itself
	std::vector<Control*> children;
	Control* image = (Control*)get_child(get_child_index(this, "Image"));
	children.push_back(image);
	Control* wall = (Control*)image->get_child(get_child_index(image, "Wall"));
	children.push_back(wall);
	for(int i = 0; i < wall->get_child_count(); ++i)
	{
		children.push_back((Control*)wall->get_child(i));
		for(int j = 0; j < wall->get_child(i)->get_child_count(); ++j)
		{
			children.push_back((Control*)wall->get_child(i)->get_child(j));
		}
	}
	Control* pattern_lines = (Control*)image->get_child(get_child_index(image, "PatternLines"));
	children.push_back(pattern_lines);
	for (int i = 0; i < pattern_lines->get_child_count(); ++i)
	{
		children.push_back((Control*)pattern_lines->get_child(i));
	}
	for(auto&& child:children)
	{
		child->connect("mouse_entered", this, "mouse_entered");
		child->connect("mouse_exited", this, "mouse_exited");
		child->connect("gui_input", this, "image_input");
	}
}

void godot::Board::_ready()
{
	OptionButton* player_select = (OptionButton*)get_child(get_child_index(this, "PlayerSelect"));
	player_select->add_item("Human", 0);
	auto ai_factories = AI::AIFactory::get_factories();
	int64_t player_index = 1;
	for (auto&& ai_factory : ai_factories)
	{
		player_select->add_item(ai_factory.first, player_index++);
	}
	connect_children();
}

void Board::_hide_player_select()
{
	OptionButton* selector = (OptionButton*)get_child(get_child_index(this, "PlayerSelect"));
	selector->set_visible(false);
}

void Board::mouse_entered()
{
	if(get("player_select"))
	{
		set_highlight(true);
	}
}

void Board::mouse_exited()
{
	if (get("player_select"))
	{
		set_highlight(false);
	}
}

void Board::image_input()
{
	if (get("player_select"))
	{
		Input* input = Input::get_singleton();
		int64_t mouse_mask = input->get_mouse_button_mask();
		if(mouse_mask&1)
		{
			emit_signal("selected", get("index"));
			set_highlight(false);
		}
	}
		
}

String Board::get_player_name()
{
	OptionButton* player_select = (OptionButton*)get_child(get_child_index(this, "PlayerSelect"));
	return player_select->get_text();
}
