#include "TileLoader.h"
#include <Sprite.hpp>

using namespace godot;

void TileLoader::_register_methods()
{
	register_method("_process", &TileLoader::_process);
	register_method("_ready", &TileLoader::_ready);
}

void TileLoader::_ready()
{
	Node2D* n = (Node2D*)tileScene->instance();
	Sprite* sprite = (Sprite*)n->get_child(0)->get_child(0);
	sprite->set_texture(blackTexture);
	n->set_position(Vector2(128.f, 128.f));
	n->set_scale(Vector2(0.2f, 0.2f));
	add_child(n);
}

void TileLoader::_init()
{
}

void TileLoader::_process(float delta)
{
}

TileLoader::TileLoader()
{
	ResourceLoader* rl = ResourceLoader::get_singleton();
	tileScene = rl->load("res://Tile.tscn");
	blackTexture = rl->load("res://Textures/black-tile.png");
	whiteTexture = rl->load("res://Textures/white-tile.png");
	blueTexture = rl->load("res://Textures/blue-tile.png");
	redTexture = rl->load("res://Textures/red-tile.png");
	yellowTexture = rl->load("res://Textures/yellow-tile.png");
}

