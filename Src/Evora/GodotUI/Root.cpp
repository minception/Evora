#include "Root.h"

using namespace godot;

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
}

void godot::Root::_init()
{
}

void Root::_ready()
{
	m_game->shuffle_bag();
	m_game->fill_factories();
	m_game->draw(get_viewport_rect().size);
}
