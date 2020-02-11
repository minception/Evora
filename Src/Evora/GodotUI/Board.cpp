#include "Board.h"
#include "Utils.h"
#include <TextureRect.hpp>
#include <Control.hpp>
#include <Input.hpp>
#include "PatternLine.h"
#include "Floor.h"
#include <Label.hpp>
#include <string>
#include "GodotScenes.h"

using namespace godot;

void Board::set_highlight(bool cond)
{
	TextureRect* image = (TextureRect*)get_child(get_child_index(this, "Image"));
	TextureRect* highlight = (TextureRect*)image->get_child(get_child_index(image, "Highlight"));
	highlight->set_visible(cond);
}

void Board::_register_methods() {
	register_method("_ready", &Board::_ready);

	register_method("mouse_entered", &Board::mouse_entered);
	register_method("mouse_exited", &Board::mouse_exited);
	register_method("image_input", &Board::image_input);
	register_method("pattern_line_entered", &Board::pattern_line_entered);
	register_method("tile_moved", &Board::tile_moved);
	register_method("tile_over", &Board::tile_over);

	register_property("index", &Board::index, 0);
	register_property("player_select", &Board::player_select, false);

	register_signal<Board>("selected", "index", GODOT_VARIANT_TYPE_INT);
	register_signal<Board>("pattern_line_entered", "pattern_line_index", GODOT_VARIANT_TYPE_INT, "board_index", GODOT_VARIANT_TYPE_INT);
	register_signal<Board>("tile_moved", "position", GODOT_VARIANT_TYPE_VECTOR2, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<Board>("tile_over","pattern_line_index", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT, "board_index", GODOT_VARIANT_TYPE_INT);
	register_signal<Board>("animation_finished", Dictionary());
}

void godot::Board::_init()
{
	
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
		children.push_back((Control*)pattern_lines->get_child(i)->get_child(0));
		pattern_lines->get_child(i)->connect("mouse_entered_pattern_line", this, "pattern_line_entered");
		pattern_lines->get_child(i)->connect("tile_over", this, "tile_over");
		connect("tile_moved", pattern_lines->get_child(i), "tile_moved");
	}
	for(auto&& child:children)
	{
		child->connect("mouse_entered", this, "mouse_entered");
		child->connect("mouse_exited", this, "mouse_exited");
		child->connect("gui_input", this, "image_input");
	}
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

void Board::pattern_line_entered(int pattern_line_index)
{
	int index = get("index");
	emit_signal("pattern_line_entered", index, pattern_line_index);
}

void Board::tile_moved(Vector2 position, int color)
{
	emit_signal("tile_moved", position, color);
}

void Board::tile_over(int pattern_line_index, int color)
{
	int index = get("index");
	emit_signal("tile_over", index, pattern_line_index, color);
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

void Board::set_pattern_line_highlight(int index, bool cond)
{
	cast_to<PatternLine>(get_node("Image/PatternLines")->get_child(index))->set_highlight(cond);
}

String Board::get_player_name()
{
	OptionButton* player_select = (OptionButton*)get_child(get_child_index(this, "PlayerSelect"));
	return player_select->get_text();
}

int Board::get_pattern_line_hover_index()
{
	Node* pattern_lines = get_node("Image/PatternLines");
	int pattern_line_count = get_node("Image/PatternLines")->get_child_count();
	for(int i = 0; i < pattern_line_count; ++i)
	{
		PatternLine* pattern_line = cast_to<PatternLine>(pattern_lines->get_child(i));
		if (pattern_line->is_mouse_over()) return i;
	}
	return -1;
}

std::vector<Vector2> Board::get_pattern_line_positions(int pattern_line_index, int count)
{
	PatternLine* pattern_line = cast_to<PatternLine>(get_node("Image/PatternLines")->get_child(pattern_line_index));
	return pattern_line->get_n_positions(count);
}

std::vector<Vector2> Board::get_floor_positions(int count)
{
	Floor* floor = (Floor*)get_node("Image/Floor");
	return floor->get_n_positions(count);
}

Vector2 Board::get_wall_position(int line, int color)
{
	int row = (color + line) % 5;
	return cast_to<TextureRect>(get_node("Image/Wall")->get_child(line)->get_child(row))->get_global_position();
}

void Board::display_score(const std::vector<int>& score_indices, int line, int color, int score)
{
	const int H_FIRST(0), H_LAST(1), V_FIRST(2), V_LAST(3);
	int row = (color + line) % 5;
	TextureRect* h_highlight = cast_to<TextureRect>(get_node("Image/HScoreHighlight"));
	TextureRect* v_highlight = cast_to<TextureRect>(get_node("Image/VScoreHighlight"));
	Vector2 h_highlight_position = cast_to<TextureRect>(get_node("Image/Wall")->get_child(score_indices[H_FIRST])->get_child(row))->get_global_position();
	Vector2 v_highlight_position = cast_to<TextureRect>(get_node("Image/Wall")->get_child(line)->get_child(score_indices[V_FIRST]))->get_global_position();
	int h_count = score_indices[H_LAST] - score_indices[H_FIRST] + 1;
	int v_count = score_indices[V_LAST] - score_indices[V_FIRST] + 1;
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	Label* score_label = cast_to<Label>(get_node("Image/Score"));
	int current_score = std::stoi(score_label->get_text().alloc_c_string());
	current_score += score;
	score_label->set_text(std::to_string(current_score).c_str());
	emit_signal("animation_finished");
}

