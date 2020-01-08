#include "TileLoader.h"
#include <Sprite.hpp>
#include <vector>

using namespace godot;

void TileLoader::_register_methods()
{
	register_method("_process", &TileLoader::_process);
	register_method("_ready", &TileLoader::_ready);
}

void TileLoader::_ready()
{
	std::vector<Node2D*> tiles;
	for (int i = 0; i < 10; ++i)
	{
		Node2D* tile = (Node2D*)tileScene->instance();
		tiles.push_back(tile);
		((Sprite*)tile->get_child(0)->get_child(0))->set_texture(blueTexture);
		tile->set_scale(Vector2(0.125, 0.125));
		tile->set_position(Vector2(35 * (i + 1), 35));
		add_child(tile);
	}
	Node2D* n = (Node2D*)tileScene->instance();
	Sprite* sprite = (Sprite*)n->get_child(0)->get_child(0);
	sprite->set_texture(blackTexture);
	n->set_position(Vector2(128.f, 128.f));
	n->set_scale(Vector2(0.125f, 0.125f));
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

