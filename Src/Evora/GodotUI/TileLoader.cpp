#include "TileLoader.h"
#include <Sprite.hpp>
#include "ObjectLoader.h"
#include "GodotTile.h"
#include <ResourceLoader.hpp>
#include <TextureRect.hpp>
#include "Utils.h"
#include "GodotScenes.h"

using namespace godot;

Root* TileLoader::p_root;

void godot::TileLoader::_register_methods()
{
	register_method("_ready", &TileLoader::_ready);
	register_method("tile_mouse_entered", &TileLoader::tile_mouse_entered);
	register_method("tile_mouse_exited", &TileLoader::tile_mouse_exited);
	register_method("tile_following", &TileLoader::tile_following);
	register_method("tile_dropped", &TileLoader::tile_dropped);
	register_method("tile_moved", &TileLoader::tile_moved);

	register_property("holding_color", &TileLoader::holding_color, -1);

	register_signal<TileLoader>("tile_moved", "position", GODOT_VARIANT_TYPE_VECTOR2, "color", GODOT_VARIANT_TYPE_INT);
}


void godot::TileLoader::_ready()
{
	ObjectLoader::tile_loader = this;
}

void godot::TileLoader::_init()
{
	holding_color = -1;
}

void TileLoader::add_tile(Vector2 position, tile color, int factory)
{
	GodotTile* to_add = (GodotTile*)GodotScenes::tile_scene->instance();
	to_add->set_position(position);
	
	to_add->connect("mouse_entered", this, "tile_mouse_entered");
	to_add->connect("mouse_exited", this, "tile_mouse_exited");
	to_add->connect("following", this, "tile_following");
	to_add->connect("dropped", this, "tile_dropped");
	to_add->connect("tile_moved", this, "tile_moved");
	
	to_add->set("color", (int)color);
	to_add->set("factory_index", factory);

	// for debug purposes
	to_add->set("interactive", true);
	
	add_child(to_add);
}

void TileLoader::tile_following(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->set_follow(factory, color, true);
	}
	set("holding_color", color);
}

void TileLoader::tile_dropped(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->set_follow(factory, color, false);
		tile->set_move_back(factory, color, true);
	}
}

void TileLoader::tile_moved(Vector2 position, int color)
{
	emit_signal("tile_moved", position, color);
}

void TileLoader::tile_mouse_entered(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->set_highlight(factory, color, true);
	}
}

void TileLoader::tile_mouse_exited(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->set_highlight(factory, color, false);
	}
}

