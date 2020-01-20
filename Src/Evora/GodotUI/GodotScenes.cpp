#include "GodotScenes.h"
#include <ResourceLoader.hpp>
#include "Board.h"
#include "Factory.h"
#include "GodotTile.h"

using namespace godot;

Ref<PackedScene> GodotScenes::board_scene;
Ref<PackedScene> GodotScenes::tile_scene;
Ref<PackedScene> GodotScenes::factory_scene;
Board* GodotScenes::board_example;
Factory* GodotScenes::factory_example;
GodotTile* GodotScenes::tile_example;
bool GodotScenes::scenes_loaded = false;

void GodotScenes::load_scenes()
{
	if (scenes_loaded) return;
	ResourceLoader* rl = ResourceLoader::get_singleton();
	board_scene = rl->load("res://Board.tscn");
	tile_scene = rl->load("res://Tile.tscn");
	factory_scene = rl->load("res://Factory.tscn");
	board_example = (Board*)GodotScenes::board_scene->instance();
	factory_example = (Factory*)GodotScenes::factory_scene->instance();
	tile_example = (GodotTile*)GodotScenes::tile_scene->instance();
	scenes_loaded = true;
}
