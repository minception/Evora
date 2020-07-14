#include "azul_game_move.h"
#include <iostream>
#include "center_offer.h"
#include "drop_center.h"
#include "factory_offer.h"
#include "drop_factory.h"
#include <memory>
#include <string>

azul_game_move::azul_game_move(int move) :
	m_move(move)
{
	int mask = 0b1111;
	m_factory_id = m_move & mask;
	m_pattern_line = (m_move >> 4) & mask;
	m_color = (m_move >> 8) & mask;
}

azul_game_move::~azul_game_move()
{
}

int azul_game_move::get_move() const
{
	return m_move;
}

std::unique_ptr<control::command> azul_game_move::generate_command(int player_index) const
{
	if (m_factory_id < 5)
	{

		if (m_pattern_line < model::COLORS)
		{
			return std::make_unique<control::factory_offer>(m_factory_id, player_index, m_pattern_line, (model::tile)m_color);
		}
		return std::make_unique<control::drop_factory>(m_factory_id, player_index, (model::tile)m_color);
	}
	if (m_pattern_line < model::COLORS)
	{
		return std::make_unique<control::center_offer>(player_index, m_pattern_line, (model::tile)m_color);
	}
	return std::make_unique<control::drop_center>(player_index, (model::tile)m_color);
}

std::string azul_game_move::to_string() const
{
	std::string color = model::tile_to_string((model::tile)m_color);
	std::string factory = m_factory_id == model::COLORS ? "center" : "factory " + std::to_string(m_factory_id);
	std::string pattern_line = m_pattern_line == model::COLORS ? "floor" : "pattern line " + std::to_string(m_pattern_line + 1);
	return color + " tile from " + factory + " to " + pattern_line;

}

bool operator==(const azul_game_move& lhs, const azul_game_move& rhs)
{
	return lhs.m_move == rhs.m_move;
}
