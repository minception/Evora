#include "Root.h"
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <OS.hpp>
#include "GodotScenes.h"
#include "Utils.h"
#include "TextureRect.hpp"

using namespace godot;

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
	register_property<Root, int>("players", &Root::number_of_players, 2);
}

void godot::Root::_init()
{
	number_of_players = 2;
	GodotScenes::load_scenes();
}

void Root::_ready()
{
	TileLoader::p_root = this;
	// Setting up window size to fit all the boards
	Vector2 board_size = ((TextureRect*)(GodotScenes::board_example->get_child(get_child_index(GodotScenes::board_example, "Image"))))->get_size();
	float width = board_size.x * number_of_players + 5 * (number_of_players + 1);
	OS::get_singleton()->set_window_size(Vector2(width, 900));
	OS::get_singleton()->center_window();
	
	// game init (maybe move this behavior over to a control class)
	get_tree()->get_root()->set_size(Vector2(width, 900));
	m_game = std::make_shared<GodotGame>(number_of_players);
	m_game->shuffle_bag();
	m_game->fill_factories();
	m_game->draw(get_viewport_rect().size);
}
