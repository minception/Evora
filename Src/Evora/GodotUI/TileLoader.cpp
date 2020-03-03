#include "TileLoader.h"
#include <Sprite.hpp>
#include "ObjectLoader.h"
#include "GodotTile.h"
#include <ResourceLoader.hpp>
#include <TextureRect.hpp>
#include "Utils.h"
#include "GodotScenes.h"
#include <string>

using namespace godot;

void godot::TileLoader::_register_methods()
{
	register_method("_ready", &TileLoader::_ready);
	register_method("tile_mouse_entered", &TileLoader::tile_mouse_entered);
	register_method("tile_mouse_exited", &TileLoader::tile_mouse_exited);
	register_method("tile_following", &TileLoader::tile_following);
	register_method("tile_dropped", &TileLoader::tile_dropped);
	register_method("tile_moved", &TileLoader::tile_moved);
	register_method("animation_finished", &TileLoader::animation_finished);
	register_method("animation_started", &TileLoader::animation_started);

	register_signal<TileLoader>("tile_moved", "position", GODOT_VARIANT_TYPE_VECTOR2, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<TileLoader>("tile_dropped", "factory", GODOT_VARIANT_TYPE_INT, "color", GODOT_VARIANT_TYPE_INT);
	register_signal<TileLoader>("animation_finished", Dictionary());
}


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
	to_add->connect("following", this, "tile_following");
	to_add->connect("dropped", this, "tile_dropped");
	to_add->connect("tile_moved", this, "tile_moved");
	to_add->connect("animation_started", this, "animation_started");
	to_add->connect("animation_finished", this, "animation_finished");
	
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
		int tile_factory = tile->get("factory_index");
		int tile_color = tile->get("color");
		if (tile_factory == factory && tile_color == color)
		{
			tile->set_follow(true);
			++holding_count;
		}
	}
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		int tile_factory = tile->get("factory_index");
		int tile_color = tile->get("color");
		if (tile_factory == factory && tile_color == color)
		{
			tile->set_text(std::to_string(holding_count).c_str());
		}
	}
	set("holding_color", color);
}

void TileLoader::tile_dropped(int factory, int color)
{
	if(--holding_count == 0)
	{
		emit_signal("tile_dropped", factory, color);
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
		int tile_factory = tile->get("factory_index");
		int tile_color = tile->get("color");
		if (tile_factory == factory && tile_color == color)
		{
			tile->set_highlight(true);
		}
	}
}

void TileLoader::tile_mouse_exited(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		int tile_factory = tile->get("factory_index");
		int tile_color = tile->get("color");
		if (tile_factory == factory && tile_color == color)
		{
			tile->set_highlight(false);
		}
	}
}

void TileLoader::snap_back(int factory, int color)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		int tile_factory = tile->get("factory_index");
		int tile_color = tile->get("color");
		if (tile_factory == factory && tile_color == color)
		{
			tile->set_follow(false);
			tile->set_move_back(true);
		}
	}
}

void TileLoader::remove_from_game(int factory_index, int color)
{
}

void TileLoader::move_tiles(int factory_index, int color, const std::vector<Vector2>& positions)
{
	int64_t child_count = get_child_count();
	int position_index = 0;
	for (int i = 0; i < child_count; ++i)
	{
		if (position_index == positions.size()) break;
		GodotTile* tile = (GodotTile*)get_child(i);
		int tile_factory = tile->get("factory_index");
		int tile_color = tile->get("color");
		if(tile_factory == factory_index && tile_color == color)
		{
			tile->set_follow(false);
			tile->set("factory_index", -1);
			tile->animate_to(positions[position_index++]);
		}
	}
}

void TileLoader::animation_started()
{
	++animating_count;
}

void TileLoader::animation_finished()
{
	if (--animating_count == 0)
	{
		emit_signal("animation_finished");
	}
}

void TileLoader::interactive(bool cond)
{
	int64_t child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		GodotTile* tile = (GodotTile*)get_child(i);
		tile->set("interactive", cond);
	}
}
