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
	register_method("tile_mouse_entered", &TileLoader::tile_mouse_entered);
	register_method("tile_mouse_exited", &TileLoader::tile_mouse_exited);
	register_method("tile_picked_up", &TileLoader::tile_picked_up);
}

Root* TileLoader::p_root;

void godot::TileLoader::_ready()
{
	ObjectLoader::tile_loader = this;
}

void godot::TileLoader::_init()
{
}

void TileLoader::add_tile(Vector2 position, tile color, int factory)
{
	GodotTile* to_add = (GodotTile*)GodotScenes::tile_scene->instance();
	to_add->set_position(position);
	to_add->connect("mouse_entered", this, "tile_mouse_entered");
	to_add->connect("mouse_exited", this, "tile_mouse_exited");
	to_add->connect("picked_up", this, "tile_picked_up");
	to_add->set("color", (int)color);
	to_add->set("factory_index", factory);
	add_child(to_add);
}

void TileLoader::tile_mouse_entered(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->highlight(factory, color);
	}
}

void TileLoader::tile_mouse_exited(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->unhighlight(factory, color);
	}
}

void TileLoader::tile_picked_up(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->pick_up(factory, color);
	}
	GodotTile::_holding_one = true;
}

