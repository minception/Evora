#include "PatternLineLoader.h"
#include <ResourceLoader.hpp>
#include "PatternLine.h"
#include <TextureRect.hpp>
#include "GodotScenes.h"
#include <ColorRect.hpp>

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
		
		Vector2 tile_size = GodotScenes::tile_example->get_size();
		float margin = 5.f;
		
		Vector2 pattern_line_size(tile_size.x * (i + 1) + margin * i, tile_size.y);
		Vector2 pattern_line_position(180 - tile_size.x * (i + 1) - margin * i, (tile_size.y + margin) * i);
		
		image->set_size(pattern_line_size);
		pattern_line->set_position(pattern_line_position);
		pattern_line->set("index", i);
		add_child(pattern_line);
	}
}
