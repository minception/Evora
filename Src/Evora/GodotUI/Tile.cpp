#include "Tile.h"

using namespace godot;

void Tile::_register_methods()
{
	register_method("_process", &Tile::_process);
}

void Tile::_init()
{
	
}

void Tile::_process(float delta)
{
}

Tile::Tile()
{
}

