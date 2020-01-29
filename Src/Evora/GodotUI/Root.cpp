#include "Root.h"

#include <OS.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

#include "GodotScenes.h"
#include "TextureRect.hpp"
#include "Utils.h"

using namespace godot;

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
	register_property<Root, int>("players", &Root::m_number_of_players, 2);
}

void godot::Root::_init()
{
	
	GodotScenes::load_scenes();
}

void Root::_ready()
{
	TileLoader::p_root = this;
	// Setting up window size to fit all the boards
	Vector2 board_size = ((TextureRect*)(GodotScenes::board_example->get_child(get_child_index(GodotScenes::board_example, "Image"))))->get_size();
	float width = board_size.x * m_number_of_players + 5 * (m_number_of_players + 1);
	OS::get_singleton()->set_window_size(Vector2(width, 900));
	OS::get_singleton()->center_window();
	
	// game init (maybe move this behavior over to a control class)
	get_tree()->get_root()->set_size(Vector2(width, 900));
	m_game = std::make_shared<GodotGame>(m_number_of_players);
	m_game->draw(get_viewport_rect().size);
}
