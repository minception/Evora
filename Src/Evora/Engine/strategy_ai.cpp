#include "strategy_ai.h"
#include "utils.h"
#include "center_offer.h"
#include "strategy_move.h"
#include <algorithm>
#include <map>

std::map<int, std::vector<strategy_move>> ai::strategy_ai::sort_moves(const std::vector<strategy_move>& moves)
{
	std::map<int, std::vector<strategy_move>> res;
	for (auto && move : moves)
	{
		std::tuple<int, int> position = move.get_wall_position();
		int key = std::get<0>(position) * model::COLORS + std::get<1>(position);
		
		res[key].push_back(move);
	}
	return res;
}

std::vector<std::pair<int, float>> ai::strategy_ai::calculate_possible_fill(
	const std::map<int, std::vector<strategy_move>>& sorted_moves)
{
	std::vector<std::pair<int, float>> res;
	std::shared_ptr<model::game> model = m_controller->get_model();
	for (auto && position : sorted_moves)
	{
		if(position.first >= 0)
		{
			
			int pattern_line = position.first / model::COLORS;
			res.emplace_back(position.first, model->get_pattern_line_tile_count(m_board_index, pattern_line));
			for (auto&& move : position.second)
			{
				res.back().second += move.get_tile_count();
			}
		}
		else
		{
			res.emplace_back(position.first, 0);
		}
	}
	return res;
}

std::tuple<int, int> ai::strategy_ai::calculate_coordinates(int position)
{
	return std::make_tuple(position % model::COLORS, position / model::COLORS);
}

void ai::strategy_ai::move()
{
	
	m_controller->add_command(pick_move());
	m_controller->step();
}

const char* ai::strategy_ai::get_name() const
{
	return "StrategyAI";
}

std::unique_ptr<control::command> ai::strategy_ai::pick_move()
{

	std::vector<strategy_move> moves = get_moves();
	std::map<int, std::vector<strategy_move>> sorted_moves = sort_moves(moves);
	std::vector<std::pair<int, float>> possible_fill = calculate_possible_fill(sorted_moves);
	std::sort(possible_fill.begin(), possible_fill.end(), [](auto a, auto b) {return a.second > b.second; });
	return sorted_moves[possible_fill[0].first].begin()->gen_move();
}

std::vector<strategy_move> ai::strategy_ai::get_moves()
{
	std::shared_ptr<model::game> model = m_controller->get_model();
	std::vector<strategy_move> res;
	for (int factory_index = 0; factory_index <= m_controller->get_model()->factory_count(); ++factory_index)
	{
		std::vector<model::tile> colors;
		if (factory_index == model->factory_count())
		{
			colors = model->get_center_colors();
		}
		else
		{
			colors = model->get_factory_colors(factory_index);
		}
		for (auto&& color : colors)
		{
			for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
			{
				if (model->can_add_to_pattern_line(m_board_index, pattern_line_index, color))
				{
					res.emplace_back(model, m_board_index, factory_index, pattern_line_index, color);
				}
			}
			// for every color adding move to floor
			res.emplace_back(model, m_board_index, factory_index, model::COLORS, color);
		}
	}
	return res;
}
