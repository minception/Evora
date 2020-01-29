#include "Root.h"

#include <OS.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Button.hpp>

#include "GodotScenes.h"
#include "TextureRect.hpp"
#include "Utils.h"

using namespace godot;

void Root::add_start_button()
{
	Button* start_button = (Button*)GodotScenes::start_button_scene->instance();
	float center_x = (get_tree()->get_root()->get_size().x - start_button->get_size().x) / 2;
	float center_y = 300 - start_button->get_size().y / 2;
	start_button->set_global_position(Vector2(center_x, center_y));
	add_child(start_button);
	start_button->connect("pressed", this, "start_game");
}

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
	register_method("start_game", &Root::start_game);
	
	register_property<Root, int>("players", &Root::m_number_of_players, 2);
}

void godot::Root::_init()
{
	m_number_of_players = 2;
	GodotScenes::load_scenes();
	
}

void Root::_ready()
{
	TileLoader::p_root = this;
	// Setting up window size to fit all the boards
	Vector2 board_size = ((TextureRect*)(GodotScenes::board_example->get_child(get_child_index(GodotScenes::board_example, "Image"))))->get_size();
	const int boards_margin = 10;
	float width = board_size.x * m_number_of_players + boards_margin * (m_number_of_players + 1);
	float height = 900.f;
	OS::get_singleton()->set_window_size(Vector2(width, height));
	OS::get_singleton()->center_window();

	// game init (maybe move this behavior over to a control class)
	get_tree()->get_root()->set_size(Vector2(width, height));
	m_game = std::make_shared<GodotGame>(m_number_of_players);
	m_game->draw(get_viewport_rect().size);

	// Add start button
	add_start_button();
}

void Root::start_game()
{
	Node2D* boards = (Node2D*)get_child(get_child_index(this, "Boards"));
	int64_t boards_count = boards->get_child_count();
	// hide player selection and prepare for starting player select
	for(int i = 0; i < boards_count; ++i)
	{
		Board* board = (Board*)boards->get_child(i);
		board->_hide_player_select();
		board->set("player_select", true);
	}
	// hide start game button
	Button* start_button = (Button*)get_child(get_child_index(this, "StartButton"));
	start_button->set_visible(false);
}
