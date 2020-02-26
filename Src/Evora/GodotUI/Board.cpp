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
#include "ColorHighlight.h"

using namespace godot;

void Board::set_highlight(bool cond)
{
	TextureRect* image = (TextureRect*)get_child(get_child_index(this, "Image"));
	TextureRect* highlight = (TextureRect*)image->get_child(get_child_index(image, "Highlight"));
	highlight->set_visible(cond);
}

void Board::_register_methods() {
	register_method("_ready", &Board::_ready);
	register_method("_process", &Board::_process);

	register_method("mouse_entered", &Board::mouse_entered);
	register_method("mouse_exited", &Board::mouse_exited);
	register_method("image_input", &Board::image_input);
	register_method("pattern_line_entered", &Board::pattern_line_entered);
	register_method("tile_moved", &Board::tile_moved);
	register_method("tile_over", &Board::tile_over);

	register_property("index", &Board::index, 0);
	register_property("player_select", &Board::player_select, false);
	register_property("time_remaining", &Board::time_remaining, 0.f);

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

void Board::_process(float delta)
{
	if(time_remaining > 0)
	{
		time_remaining -= delta;
		if(time_remaining <= 0)
		{
			TextureRect* h_highlight = cast_to<TextureRect>(get_node("Image/ScoreHighlights/HScoreHighlight"));
			TextureRect* v_highlight = cast_to<TextureRect>(get_node("Image/ScoreHighlights/VScoreHighlight"));
			ColorHighlight* color_highlight = cast_to<ColorHighlight>(get_node("Image/ScoreHighlights/ColorHighlight"));
			h_highlight->set_visible(false);
			v_highlight->set_visible(false);
			color_highlight->unhighlight();
			emit_signal("animation_finished");
		}
	}
}

void Board::connect_children()
{
	// I had to put this here, because children kept stealing focus from the board itself
	std::vector<Control*> children;
	Control* image = (Control*)get_child(get_child_index(this, "Image"));
	children.push_back(image);
	children.push_back((Control*)image->get_node("WallBackground"));
	children.push_back((Control*)image->get_node("Separator"));
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
	Control* pattern_lines = (Control*)image->get_node("PatternLines");
	children.push_back(pattern_lines);
	for (int i = 0; i < pattern_lines->get_child_count(); ++i)
	{
		children.push_back((Control*)pattern_lines->get_child(i)->get_node("Image"));
		pattern_lines->get_child(i)->connect("mouse_entered_pattern_line", this, "pattern_line_entered");
		pattern_lines->get_child(i)->connect("tile_over", this, "tile_over");
		connect("tile_moved", pattern_lines->get_child(i), "tile_moved");
	}
	children.push_back((Control*)image->get_node("Floor/Image"));
	image->get_node("Floor")->connect("tile_over", this, "tile_over");
	
	connect("tile_moved", image->get_node("Floor"), "tile_moved");

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
			int index = get("index");
			emit_signal("selected", index);
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
	Floor* floor = cast_to<Floor>(get_node("Image/Floor"));
	if (floor->is_mouse_over()) return 5;
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

std::vector<Vector2> Board::get_wall_color_positions(int color)
{
	std::vector<Vector2> positions;
	Node* wall = get_node("Image/Wall");// ->get_child(line)->get_child(row))->get_global_position();
	for (int line = 0; line < COLORS; ++line)
	{
		int row = (line + color) % COLORS;
		positions.push_back(cast_to<TextureRect>(wall->get_child(line)->get_child(row))->get_global_position());
	}
	return positions;
}

Vector2 Board::get_wall_position(int line, int color)
{
	int row = (color + line) % 5;
	return cast_to<TextureRect>(get_node("Image/Wall")->get_child(line)->get_child(row))->get_global_position();
}

Vector2 godot::Board::get_starter_tile_position()
{
	Vector2 position = get_global_position();
	Vector2 size = cast_to<TextureRect>(get_node("Image"))->get_size();
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	float margin = 5.f;
	return Vector2(position.x + size.x - margin - tile_size.x, position.y + margin);
}

void Board::display_wall_tile_score(const std::vector<int>& score_indices, int line, int color, int score)
{
	const int H_FIRST(0), H_LAST(1), V_FIRST(2), V_LAST(3);
	int row = (color + line) % 5;
	TextureRect* h_highlight = cast_to<TextureRect>(get_node("Image/ScoreHighlights/HScoreHighlight"));
	TextureRect* v_highlight = cast_to<TextureRect>(get_node("Image/ScoreHighlights/VScoreHighlight"));
	Vector2 h_highlight_position = cast_to<TextureRect>(get_node("Image/Wall")->get_child(line)->get_child(score_indices[H_FIRST]))->get_global_position();
	Vector2 v_highlight_position = cast_to<TextureRect>(get_node("Image/Wall")->get_child(score_indices[V_FIRST])->get_child(row))->get_global_position();
	int h_count = score_indices[H_LAST] - score_indices[H_FIRST] + 1;
	int v_count = score_indices[V_LAST] - score_indices[V_FIRST] + 1;
	Vector2 tile_size = cast_to<TextureRect>(GodotScenes::tile_example->get_node("Image"))->get_size();
	float margin = 5.f;
	Vector2 h_highlight_size = Vector2(tile_size.x * h_count + margin * (h_count - 1), tile_size.y);
	Vector2 v_highlight_size = Vector2(tile_size.x, tile_size.y * v_count + margin * (v_count - 1));

	h_highlight->set_global_position(h_highlight_position);
	h_highlight->set_size(h_highlight_size);
	h_highlight->set_visible(true);
	v_highlight->set_global_position(v_highlight_position);
	v_highlight->set_size(v_highlight_size);
	v_highlight->set_visible(true);
	
	increase_score(score);
	
	set("time_remaining", 1.f);
}

void Board::display_wall_color_score(int color, int score)
{
	ColorHighlight* color_highlight = cast_to<ColorHighlight>(get_node("Image/ScoreHighlights/ColorHighlight"));
	color_highlight->highlight(get_wall_color_positions(color));
	
	increase_score(score);
	
	set("time_remaining", 1.f);
}

void Board::display_wall_line_score(int line, int score)
{
	TextureRect* h_highlight = cast_to<TextureRect>(get_node("Image/ScoreHighlights/HScoreHighlight"));
	Control* line_display = cast_to<Control>(get_node("Image/Wall")->get_child(line));
	h_highlight->set_global_position(line_display->get_global_position());
	h_highlight->set_size(line_display->get_size());
	h_highlight->set_visible(true);

	increase_score(score);
	
	set("time_remaining", 1.f);
}

void Board::display_wall_row_score(int row, int score)
{
	TextureRect* v_highlight = cast_to<TextureRect>(get_node("Image/ScoreHighlights/VScoreHighlight"));
	
	Control* line_display = cast_to<Control>(get_node("Image/Wall")->get_child(0));
	Control* tile_display = cast_to<Control>(line_display->get_child(row));
	v_highlight->set_global_position(tile_display->get_global_position());
	v_highlight->set_size(Vector2(tile_display->get_size().x, line_display->get_size().x));
	v_highlight->set_visible(true);
	
	increase_score(score);
	
	set("time_remaining", 1.f);
}

void Board::increase_score(int score)
{
	Label* score_label = cast_to<Label>(get_node("Image/Score"));
	int current_score = std::stoi(score_label->get_text().alloc_c_string());
	current_score += score;
	score_label->set_text(std::to_string(current_score).c_str());
}

void Board::set_floor_highlight(bool cond)
{
	Floor* floor = (Floor*)get_node("Image/Floor");
	floor->set_highlight(cond);
}

void Board::display_floor_score(int score)
{
	increase_score(score);
}

