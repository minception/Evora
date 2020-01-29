#include "GameData.h"

using namespace godot;

void GameData::_register_methods()
{
	register_property("number_of_players", &GameData::number_of_players, 2);
	register_property("current_player", &GameData::current_player, 0);
}

void GameData::add_player(std::unique_ptr<Player> player)
{
	players.push_back(std::move(player));
}

void GameData::_init()
{
	number_of_players = 2;
	m_game = std::make_shared<model::game>(number_of_players);
	controller = std::make_shared<control::game_controller>(m_game);
}
