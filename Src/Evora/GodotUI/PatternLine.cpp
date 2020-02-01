#include "PatternLine.h"

using namespace godot;

void PatternLine::mouse_entered()
{
	TextureRect* image = (TextureRect*)get_node("Image");
	image->set_self_modulate(Color(0, 1, 1));
	int index = get("index");
	emit_signal("mouse_entered_pattern_line", index);
}

void PatternLine::mouse_exited()
{
	TextureRect* image = (TextureRect*)get_node("Image");
	image->set_self_modulate(Color(1, 1, 1));
	int index = get("index");
	emit_signal("mouse_exited_pattern_line", index);
}

void PatternLine::_register_methods()
{

	register_signal<PatternLine>("mouse_exited_pattern_line", "index", GODOT_VARIANT_TYPE_INT);
	register_signal<PatternLine>("mouse_entered_pattern_line", "index", GODOT_VARIANT_TYPE_INT);

	register_method("mouse_entered", &PatternLine::mouse_entered);
	register_method("mouse_exited", &PatternLine::mouse_exited);
	register_method("_ready", &PatternLine::_ready);
	
	register_property("index", &PatternLine::set_index, &PatternLine::get_index, 0);
}

void PatternLine::_init()
{
}

void PatternLine::_ready()
{
	TextureRect* image = (TextureRect*)get_node("Image");
	image->connect("mouse_entered", this, "mouse_entered");
	image->connect("mouse_exited", this, "mouse_exited");
}
