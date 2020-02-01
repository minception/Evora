#include "PatternLineLoader.h"
#include <ResourceLoader.hpp>
#include "PatternLine.h"

using namespace godot;

Ref<PackedScene> PatternLineLoader::pattern_line_scene;

void godot::PatternLineLoader::_register_methods()
{
	register_method("_ready", &PatternLineLoader::_ready);
}

void godot::PatternLineLoader::_init()
{
	ResourceLoader* rl = ResourceLoader::get_singleton();
	pattern_line_scene = rl->load("res://PatternLine.tscn");
}

void godot::PatternLineLoader::_ready()
{
	for (int i = 0; i < 5; ++i)
	{
		PatternLine* pattern_line = (PatternLine*)pattern_line_scene->instance();
		TextureRect* image = (TextureRect*)pattern_line->get_node("Image");
		image->set_size(Vector2(32 * (i + 1) + 5 * i, 32));
		pattern_line->set_position(Vector2(180 - 32 * (i + 1) - 5 * i, 37 * i));
		pattern_line->set("index", i);
		add_child(pattern_line);
	}
}
