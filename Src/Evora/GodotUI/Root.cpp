#include "Root.h"

using namespace godot;

void godot::Root::_register_methods()
{
	
}

// ObjectLoader* Root::p_loader;
BoardLoader* Root::p_board_loader;
FactoryLoader* Root::p_factory_loader;
TileLoader* Root::p_tile_loader;

void godot::Root::_init()
{
	//m_game->draw();
}
