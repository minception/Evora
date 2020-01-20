#include "Root.h"
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <OS.hpp>

using namespace godot;

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
	register_property<Root, int>("players", &Root::number_of_players, 2);
}

void godot::Root::_init()
{
	number_of_players = 2;
}

void Root::_ready()
{
	get_tree()->get_root()->set_size(Vector2(1920, 1080));
	OS::get_singleton()->set_window_size(Vector2(1920, 1080));
	m_game = std::make_shared<GodotGame>(number_of_players);
	m_game->shuffle_bag();
	m_game->fill_factories();
	m_game->draw(get_viewport_rect().size);
}
