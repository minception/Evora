#pragma once
#include <memory>
#include "game.h"
#include "command.h"
#include <map>

class strategy_move
{
public:

	strategy_move(std::shared_ptr<model::game> model, int player_index, int factory_index, int pattern_line_index, model::tile color) :
		m_model(model),
		m_player_index(player_index),
		m_factory_index(factory_index),
		m_pattern_line_index(pattern_line_index),
		m_color(color)
	{
		calculate_parameters();
	}
	std::unique_ptr<control::command> gen_move() const;
	std::tuple<int, int> get_wall_position() const;
	float get_tile_count() const;
	int to_fill() const;
	int get_overflow() const;
private:
	std::shared_ptr<model::game> m_model;
	int m_player_index;
	int m_factory_index;
	int m_pattern_line_index;
	model::tile m_color;

	// parameters for judging the quality of the move
	float m_line_fill;
	int m_tile_count;
	int m_line_overflow;
	int m_score_gain;
	int m_to_fill;
	std::tuple<int, int> m_wall_position;
	
	void calculate_parameters();
};
