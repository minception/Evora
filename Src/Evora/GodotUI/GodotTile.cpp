#include "GodotTile.h"

using namespace godot;

void GodotTile::_register_methods() {
	register_method("_process", &GodotTile::_process);
}

void godot::GodotTile::_init()
{
}

void godot::GodotTile::_process(float delta)
{
}

godot::GodotTile::GodotTile()
{
}
