#include "TileLoader.h"

using namespace godot;

void godot::TileLoader::_register_methods()
{
	register_method("_ready", &TileLoader::_ready);
}
Ref<PackedScene> TileLoader::tileScene;
Ref<Texture> TileLoader::blackTexture;
Ref<Texture> TileLoader::whiteTexture;
Ref<Texture> TileLoader::blueTexture;
Ref<Texture> TileLoader::redTexture;
Ref<Texture> TileLoader::yellowTexture;

void godot::TileLoader::_ready()
{
	Root::p_tile_loader = this;
}

void godot::TileLoader::_init()
{
	ResourceLoader* rl = ResourceLoader::get_singleton();
	tileScene = rl->load("res://Tile.tscn");
	blackTexture = rl->load("res://Textures/black-tile.png");
	whiteTexture = rl->load("res://Textures/white-tile.png");
	blueTexture = rl->load("res://Textures/blue-tile.png");
	redTexture = rl->load("res://Textures/red-tile.png");
	yellowTexture = rl->load("res://Textures/yellow-tile.png");
}

void godot::TileLoader::_process(float delta)
{
}

godot::TileLoader::TileLoader()
{
}
