#include "Root.h"

#include <OS.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Button.hpp>

#include "GodotScenes.h"
#include "TextureRect.hpp"
#include "Utils.h"
#include "GameData.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

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

void Root::set_starting_player(int index)
{
	GameData* game_data= cast_to<GameData>(get_node("GameData"));
	game_data->set("current_player", index);
	
	for (int i = 0; i < m_number_of_players; i++)
	{
		ObjectLoader::board_loader->get_child(i)->set("player_select", false);
	}
}

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
	register_method("start_game", &Root::start_game);
	register_method("set_starting_player", &Root::set_starting_player);
	
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

	// set values in game data
	GameData* game_data = cast_to<GameData>(get_node("GameData"));
	game_data->set("number_of_players", m_number_of_players);
	
	get_tree()->get_root()->set_size(Vector2(width, height));

	// game init
	ObjectLoader::board_loader = cast_to<BoardLoader>(get_node("Boards"));
	ObjectLoader::board_loader->load_boards(m_number_of_players, Vector2(width, height));
	ObjectLoader::factory_loader = cast_to<FactoryLoader>(get_node("Factories"));
	ObjectLoader::factory_loader->load_factories(m_number_of_players*2 + 1, Vector2(width / 2, 300), 200);

	// connect signals necessito
	for(int i = 0; i < m_number_of_players; i++)
	{
		ObjectLoader::board_loader->get_child(i)->connect("selected", this, "set_starting_player");
	}
	
	add_start_button();
}

void Root::start_game()
{
	Node2D* boards = (Node2D*)get_child(get_child_index(this, "Boards"));
	int64_t boards_count = boards->get_child_count();
	
	GameData* game_data = cast_to<GameData>(get_node("GameData"));
	game_data->set("number_of_players", m_number_of_players);
	game_data->set_data();
	
	auto ai_factories = AI::AIFactory::get_factories();
	// hide player selection and prepare for starting player select
	for(int i = 0; i < boards_count; ++i)
	{
		Board* board = (Board*)boards->get_child(i);
		board->_hide_player_select();
		String player_name = board->get_player_name();
		if(player_name == "Human")
		{
			std::unique_ptr<Player> player = std::make_unique<HumanPlayer>();
			game_data->add_player(std::move(player));
		}
		else
		{
			std::unique_ptr<Player> player = std::make_unique<AIPlayer>(ai_factories.at(player_name.alloc_c_string())->get(game_data->controller));
			game_data->add_player(std::move(player));
		}
		board->set("player_select", true);
	}
	// hide start game button
	Button* start_button = (Button*)get_child(get_child_index(this, "StartButton"));
	start_button->set_visible(false);

	// tell controller to start the game
	game_data->controller->start_game();
}

void Root::animation_finished()
{
}
