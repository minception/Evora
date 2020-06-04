#include "strategy_move.h"
#include "factory_offer.h"
#include "drop_factory.h"
#include "center_offer.h"
#include "drop_center.h"


std::unique_ptr<control::command> strategy_move::gen_move() const
{
	if (m_factory_index < m_model->factory_count())
	{

		if (m_pattern_line_index < model::COLORS)
		{
			return std::make_unique<control::factory_offer>(m_factory_index, m_player_index, m_pattern_line_index, (model::tile)m_color);
		}
		return std::make_unique<control::drop_factory>(m_factory_index, m_player_index, (model::tile)m_color);
	}
	if (m_pattern_line_index < model::COLORS)
	{
		return std::make_unique<control::center_offer>(m_player_index, m_pattern_line_index, (model::tile)m_color);
	}
	return std::make_unique<control::drop_center>(m_player_index, (model::tile)m_color);
}

std::tuple<int, int> strategy_move::get_wall_position() const
{
	return m_wall_position;
}

float strategy_move::get_tile_count() const
{
	return m_tile_count;
}

int strategy_move::to_fill() const
{
	return m_to_fill;
}

int strategy_move::get_overflow() const
{
	return m_line_overflow;
}

void strategy_move::calculate_parameters()
{
	if (m_factory_index < m_model->factory_count())
	{
		m_tile_count = m_model->factory_tile_count(m_factory_index, m_color);
	}
	else
	{
		m_tile_count = m_model->center_tile_count(m_color);
	}
	if (m_pattern_line_index < model::COLORS)
	{
		m_to_fill = m_pattern_line_index - m_model->get_pattern_line_tile_count(m_player_index, m_pattern_line_index);
		m_line_overflow = m_tile_count > m_to_fill ? m_tile_count - m_to_fill : 0;
		int row = (m_pattern_line_index + static_cast<int>(m_color)) % model::COLORS;
		m_wall_position = std::make_tuple(m_pattern_line_index, row);
		m_line_fill = (m_pattern_line_index + 1) / static_cast<float>(m_tile_count);
	}
	else
	{
		m_to_fill = 0;
		m_wall_position = std::make_tuple(0, -1);
		m_line_overflow = m_tile_count;
	}
	
}
