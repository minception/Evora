#include "GodotScenes.h"
#include <ResourceLoader.hpp>
#include "Board.h"
#include "Factory.h"
#include "GodotTile.h"
#include "GameData.h"

using namespace godot;

Ref<PackedScene> GodotScenes::board_scene;
Ref<PackedScene> GodotScenes::tile_scene;
Ref<PackedScene> GodotScenes::factory_scene;
Ref<PackedScene> GodotScenes::start_button_scene;
Ref<PackedScene> GodotScenes::step_button_scene;
Ref<PackedScene> GodotScenes::center_scene;
Board* GodotScenes::board_example;
Factory* GodotScenes::factory_example;
GodotTile* GodotScenes::tile_example;
Button* GodotScenes::start_button_example;
Button* GodotScenes::step_button_example;
GameData* GodotScenes::game_data;
Root* GodotScenes::root;
bool GodotScenes::scenes_loaded = false;

void GodotScenes::load_scenes()
{
	if (scenes_loaded) return;
	ResourceLoader* rl = ResourceLoader::get_singleton();
	board_scene = rl->load("res://Board.tscn");
	tile_scene = rl->load("res://Tile.tscn");
	factory_scene = rl->load("res://Factory.tscn");
	start_button_scene = rl->load("res://StartButton.tscn");
	step_button_scene = rl->load("res://StepButton.tscn");
	center_scene = rl->load("res://Center.tscn");
	board_example = (Board*)board_scene->instance();
	factory_example = (Factory*)factory_scene->instance();
	tile_example = (GodotTile*)tile_scene->instance();
	start_button_example = (Button*)start_button_scene->instance();
	step_button_example = (Button*)step_button_scene->instance();
	scenes_loaded = true;
}
