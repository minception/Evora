#pragma once
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include "Board.h"
#include "Factory.h"
#include "GodotTile.h"
#include <Button.hpp>
#include "GameData.h"

using namespace godot;

struct GodotScenes
{
	static Ref<PackedScene> board_scene;
	static Ref<PackedScene> tile_scene;
	static Ref<PackedScene> factory_scene;
	static Ref<PackedScene> start_button_scene;
	static Board* board_example;
	static Factory* factory_example;
	static GodotTile* tile_example;
	static Button* start_button_example;
	static GameData* game_data;
	static void load_scenes();
private:
	static bool scenes_loaded;
};
