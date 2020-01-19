#include "TileLoader.h"
#include <Sprite.hpp>
#include "ObjectLoader.h"
#include "GodotTile.h"
#include <ResourceLoader.hpp>

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
Ref<Texture> TileLoader::starterTexture;

void godot::TileLoader::_ready()
{
	ObjectLoader::tile_loader = this;
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
	starterTexture = rl->load("res://Textures/starter-tile.png");
}

void godot::TileLoader::_process(float delta)
{
}

void TileLoader::add_tile(Vector2 position, tile color)
{
	GodotTile* to_add = (GodotTile*)tileScene->instance();
	Sprite* sprite = (Sprite*)to_add->get_child(0)->get_child(0);
	switch (color)
	{
	case model::tile::black:
		sprite->set_texture(blackTexture);
		break;
	case model::tile::blue:
		sprite->set_texture(blueTexture);
		break;
	case model::tile::red:
		sprite->set_texture(redTexture);
		break;
	case model::tile::white:
		sprite->set_texture(whiteTexture);
		break;
	case model::tile::yellow:
		sprite->set_texture(yellowTexture);
		break;
	case model::tile::starter:
		sprite->set_texture(starterTexture);
		break;
	case model::tile::empty:
		sprite->set_texture(nullptr);
		break;
	}
	to_add->set_position(position);
	to_add->set_scale(Vector2(0.125f, 0.125f));
	add_child(to_add);
}

godot::TileLoader::TileLoader()
{
}
