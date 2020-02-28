#include "Root.h"

#include <OS.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Button.hpp>
#include <AnimationPlayer.hpp>
#include <Animation.hpp>
#include <CanvasItem.hpp>

#include "GodotScenes.h"
#include "TextureRect.hpp"
#include "Utils.h"
#include "GameData.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "factory_offer.h"
#include "center_offer.h"
#include "Center.h"
#include "drop_center.h"
#include "drop_factory.h"
#include <string>
#include <Label.hpp>

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
	GameData* game_data = cast_to<GameData>(get_node("GameData"));
	game_data->current_player = index;

	// hide gui aspects of player select
	for (int i = 0; i < m_number_of_players; i++)
	{
		ObjectLoader::board_loader->get_child(i)->set("player_select", false);
	}
	cast_to<Control>(get_node("Shade"))->set_visible(false);
	cast_to<Control>(get_node("SelectPlayerPrompt"))->set_visible(false);

	GodotTile* starter_tile = cast_to<GodotTile>(get_node("StarterTile"));
	starter_tile->set_color((int)tile::starter);

	game_data->controller->set_first_player(index);
	game_data->controller->start_game();
	//game_data->players[index]->move();

	Board* highlighted = cast_to<Board>(ObjectLoader::board_loader->get_child(index));
	TextureRect* player_highlight = cast_to<TextureRect>(get_node("PlayerHighlight"));
	player_highlight->set_global_position(highlighted->get_global_position() - Vector2(3, 3));
	player_highlight->set_visible(true);
	
	// show step button
	if (m_stepping)
	{
		add_child(GodotScenes::step_button_example);
		Vector2 viewport_size = get_viewport_rect().size;
		Vector2 step_button_size = GodotScenes::step_button_example->get_size();
		GodotScenes::step_button_example->set_position(Vector2(viewport_size.x - step_button_size.x - 5.f, 5.f));
		GodotScenes::step_button_example->connect("pressed", this, "step");
		ObjectLoader::tile_loader->interactive(false);
	}
	
}

void Root::move_highlight(int player_index)
{
	Node* animations_owner = get_node("PlayerChangeAnimations");
	Board* next_player = (Board*)ObjectLoader::board_loader->get_child(player_index);
	AnimationPlayer* animationPlayer = AnimationPlayer::_new();
	Animation* animation = Animation::_new();
	animationPlayer->add_animation("animation", animation);
	animationPlayer->set_current_animation("animation");
	animation->add_track(Animation::TrackType::TYPE_VALUE);
	animation->track_set_path(0, "../PlayerHighlight:rect_position");
	animation->track_insert_key(0, 0.0, ((Control*)get_node("PlayerHighlight"))->get_global_position());
	animation->track_insert_key(0, 0.2, next_player->get_global_position() - Vector2(3.0, 3.0));
	animation->track_set_interpolation_type(0, Animation::InterpolationType::INTERPOLATION_CUBIC);
	animations_owner->add_child(animationPlayer);
	animationPlayer->play();
}

void godot::Root::_register_methods()
{
	register_method("_ready", &Root::_ready);
	register_method("start_game", &Root::start_game);
	register_method("set_starting_player", &Root::set_starting_player);
	register_method("pattern_line_entered", &Root::pattern_line_entered);
	register_method("tile_over", &Root::tile_over);
	register_method("tile_dropped", &Root::tile_dropped);
	register_method("animation_finished", &Root::animation_finished);
	register_method("step", &Root::step);

	register_property("players", &Root::m_number_of_players, 2);
}

void godot::Root::_init()
{
	m_number_of_players = 2;
	GodotScenes::load_scenes();
}

void Root::_ready()
{
	// Setting up window size to fit all the boards
	Vector2 board_size = ((TextureRect*)(GodotScenes::board_example->get_child(
		get_child_index(GodotScenes::board_example, "Image"))))->get_size();
	const int boards_margin = 10;
	float width = board_size.x * m_number_of_players + boards_margin * (m_number_of_players + 1);
	float height = 900.f;
	OS::get_singleton()->set_window_size(Vector2(width, height));
	OS::get_singleton()->center_window();

	// set values in game data
	GodotScenes::game_data = cast_to<GameData>(get_node("GameData"));
	GodotScenes::game_data->set("number_of_players", m_number_of_players);

	get_tree()->get_root()->set_size(Vector2(width, height));

	// game init
	ObjectLoader::board_loader->load_boards(m_number_of_players, Vector2(width, height));
	ObjectLoader::factory_loader->load_factories(m_number_of_players * 2 + 1, Vector2(width / 2, 300), 220);
	
	Center* center = (Center*)GodotScenes::center_scene->instance();
	Vector2 center_size = cast_to<Control>(center->get_node("Image"))->get_size();
	center->set_global_position(Vector2((width - center_size.x) / 2, 300 - center_size.y / 2));
	add_child_below_node(get_node("Boards"), center);

	// connect signals necessito
	for (int i = 0; i < m_number_of_players; i++)
	{
		Board* board = cast_to<Board>(ObjectLoader::board_loader->get_child(i));
		board->connect("selected", this, "set_starting_player");
		board->connect("pattern_line_entered", this, "pattern_line_entered");
		board->connect("tile_over", this, "tile_over");
		board->connect("animation_finished", this, "animation_finished");
		ObjectLoader::tile_loader->connect("tile_moved", board, "tile_moved");
	}
	ObjectLoader::tile_loader->connect("tile_dropped", this, "tile_dropped");
	ObjectLoader::tile_loader->connect("animation_finished", this, "animation_finished");
	add_start_button();

	// add root to godot scenes to be accessed from elsewhere
	GodotScenes::root = this;
}

void Root::create_player_change_animations()
{
	Board* previous_player = (Board*)ObjectLoader::board_loader->get_child(m_number_of_players - 1);
	Node* animations_owner = get_node("PlayerChangeAnimations");
	for (int i = 0; i < m_number_of_players; ++i)
	{
		Board* next_player = (Board*)ObjectLoader::board_loader->get_child(i);
		AnimationPlayer* animationPlayer = AnimationPlayer::_new();
		Animation* animation = Animation::_new();
		animationPlayer->add_animation("animation", animation);
		animationPlayer->set_current_animation("animation");
		animation->add_track(Animation::TrackType::TYPE_VALUE);
		animation->track_set_path(0, "../PlayerHighlight:rect_position");
		animation->track_insert_key(0, 0.0, previous_player->get_global_position() - Vector2(3.0, 3.0));
		animation->track_insert_key(0, 0.2, next_player->get_global_position() - Vector2(3.0, 3.0));
		animation->track_set_interpolation_type(0, Animation::InterpolationType::INTERPOLATION_CUBIC);
		animations_owner->add_child(animationPlayer);
		previous_player = next_player;
	}

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
	for (int i = 0; i < boards_count; ++i)
	{
		Board* board = (Board*)boards->get_child(i);
		board->_hide_player_select();
		String player_name = board->get_player_name();
		cast_to<Label>(board->get_node("PlayerName"))->set_text(player_name);
		if (player_name == "Human")
		{
			std::unique_ptr<Player> player = std::make_unique<HumanPlayer>();
			game_data->add_player(std::move(player));
			m_stepping = false;
		}
		else
		{
			std::unique_ptr<Player> player = std::make_unique<AIPlayer>(
				ai_factories.at(player_name.alloc_c_string())->get(game_data->controller, i));
			game_data->add_player(std::move(player));
		}
		board->set("player_select", true);
	}
	// hide start game button
	Button* start_button = (Button*)get_child(get_child_index(this, "StartButton"));
	start_button->set_visible(false);


	// show prompt to select starting player
	cast_to<Control>(get_node("Shade"))->set_visible(true);
	Control* prompt = cast_to<Control>(get_node("SelectPlayerPrompt"));
	Vector2 viewport_size = get_viewport_rect().size;
	prompt->set_global_position(Vector2((viewport_size.x - prompt->get_size().x) / 2, 300 - prompt->get_size().y / 2));
	prompt->set_visible(true);

	create_player_change_animations();
}

void Root::step()
{
	GodotScenes::game_data->players[GodotScenes::game_data->current_player]->move();
	GodotScenes::step_button_example->set_disabled(true);
}

void Root::switch_to_next_player()
{
	GodotScenes::game_data->current_player = (GodotScenes::game_data->current_player + 1) % m_number_of_players;
	AnimationPlayer* animation = (AnimationPlayer*)get_node("PlayerChangeAnimations")->get_child(GodotScenes::game_data->current_player);
	animation->play();	
}

void Root::announce_winner()
{
	_ASSERT(false);
	String winner = std::to_string(GodotScenes::game_data->m_game->get_winner() + 1).c_str();
	String text = "The winner is player number " + winner;
	cast_to<Control>(get_node("Shade"))->set_visible(true);
	Label* winner_label = cast_to<Label>(get_node("AnnounceWinner"));
	winner_label->set_text(text);
	Vector2 viewport_size = get_viewport_rect().size;
	winner_label->set_global_position(Vector2((viewport_size.x - winner_label->get_size().x) / 2, 300 - winner_label->get_size().y / 2));
	winner_label->set_visible(true);
	//Button* start_button = (Button*)get_node("StartButton");
	//start_button->set_visible(true);
}

void Root::animation_finished()
{
	if(!GodotScenes::game_data->controller->step())
	{
		if (GodotScenes::game_data->m_game->game_over())
		{
			announce_winner();
		}
		else
		{
			switch_to_next_player();
			if(!m_stepping)
			{
				GodotScenes::game_data->players[GodotScenes::game_data->current_player]->move();
			}
			else
			{
				GodotScenes::step_button_example->set_disabled(false);
			}
		}
	}
}

void Root::pattern_line_entered(int board_index, int pattern_line_index)
{
}

void Root::tile_over(int board_index, int pattern_line_index, int color)
{
	// tile is over current player's floor
	if(board_index == GodotScenes::game_data->current_player && pattern_line_index == COLORS)
	{
		cast_to<Board>(ObjectLoader::board_loader->get_child(board_index))->set_floor_highlight(true);
	}
	// tile is over current player's pattern line
	else if (board_index == GodotScenes::game_data->current_player &&
		GodotScenes::game_data->m_game->can_add_to_pattern_line(board_index, pattern_line_index, model::tile(color)))
	{
		set("tile_over_pattern_line", pattern_line_index);
		cast_to<Board>(ObjectLoader::board_loader->get_child(board_index))->set_pattern_line_highlight(
			pattern_line_index, true);
	}
}

void Root::tile_dropped(int factory_index, int color)
{
	int board_index = GodotScenes::game_data->current_player;
	Board* board = cast_to<Board>(get_node("Boards")->get_child(board_index));
	int pattern_line_index = board->get_pattern_line_hover_index();
	if(pattern_line_index == COLORS)
	{
		board->set_floor_highlight(false);
		if(factory_index == ObjectLoader::factory_loader->get_child_count())
		{
			GodotScenes::game_data->controller->add_command(
				std::move(
					std::make_unique<control::drop_center>(
						board_index,
						(model::tile)color)
				)
			);
		}
		else
		{
			GodotScenes::game_data->controller->add_command(
				std::move(
					std::make_unique<control::drop_factory>(
						factory_index,
						board_index,
						(model::tile)color)
				)
			);
		}
		board->set_floor_highlight(false);
		GodotScenes::game_data->controller->step();
	}
	else if(pattern_line_index != -1
		&& GodotScenes::game_data->m_game->can_add_to_pattern_line(board_index, pattern_line_index, model::tile(color)))
	{
		board->set_pattern_line_highlight(pattern_line_index, false);
		if(factory_index == ObjectLoader::factory_loader->get_child_count())
		{
			GodotScenes::game_data->controller->add_command(
				std::move(
					std::make_unique<control::center_offer>(
						board_index,
						pattern_line_index,
						(model::tile)color)
				)
			);
		}
		else
		{
			GodotScenes::game_data->controller->add_command(
				std::move(
					std::make_unique<control::factory_offer>(
						factory_index,
						board_index,
						pattern_line_index,
						(model::tile)color)
				)
			);
		}
		board->set_pattern_line_highlight(pattern_line_index, false);
		GodotScenes::game_data->controller->step();
	}
	else
	{
		ObjectLoader::tile_loader->snap_back(factory_index, color);
	}
}
