#include "TileLoader.h"
#include <Sprite.hpp>
#include "ObjectLoader.h"
#include "GodotTile.h"
#include <ResourceLoader.hpp>
#include <TextureRect.hpp>
#include "Utils.h"
#include "GodotScenes.h"

using namespace godot;

void godot::TileLoader::_register_methods()
{
	register_method("_ready", &TileLoader::_ready);
}
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
	blackTexture = rl->load("res://Textures/black-tile.png");
	whiteTexture = rl->load("res://Textures/white-tile.png");
	blueTexture = rl->load("res://Textures/blue-tile.png");
	redTexture = rl->load("res://Textures/red-tile.png");
	yellowTexture = rl->load("res://Textures/yellow-tile.png");
	starterTexture = rl->load("res://Textures/starter-tile.png");
}

void TileLoader::add_tile(Vector2 position, tile color)
{
	GodotTile* to_add = (GodotTile*)GodotScenes::tile_scene->instance();
	TextureRect* image = (TextureRect*)to_add->get_child(get_child_index(to_add, "Image"));
	switch (color)
	{
	case model::tile::black:
		image->set_texture(blackTexture);
		break;
	case model::tile::blue:
		image->set_texture(blueTexture);
		break;
	case model::tile::red:
		image->set_texture(redTexture);
		break;
	case model::tile::white:
		image->set_texture(whiteTexture);
		break;
	case model::tile::yellow:
		image->set_texture(yellowTexture);
		break;
	case model::tile::starter:
		image->set_texture(starterTexture);
		break;
	case model::tile::empty:
		image->set_texture(nullptr);
		break;
	}
	to_add->set_position(position);
	to_add->set_color(color);
	add_child(to_add);
}
