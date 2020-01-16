#include "Root.h"

using namespace godot;

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
}

// ObjectLoader* Root::p_loader;
BoardLoader* Root::p_board_loader;
FactoryLoader* Root::p_factory_loader;
TileLoader* Root::p_tile_loader;

void godot::Root::_init()
{
}

void Root::_ready()
{
	Vector2 viewport_size = get_viewport_rect().size;
	p_factory_loader->load_factories(5, Vector2(viewport_size.x/2, 350), 250);
}
