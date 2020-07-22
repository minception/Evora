#include "strategy_ai.h"
#include "utils.h"
#include "center_offer.h"
#include "strategy_move.h"
#include <algorithm>
#include <map>
#include <string>

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
		if(position.first >= 0 && !position.second.empty())
		{
			
			int pattern_line = position.first / model::COLORS;
			int current_fill = model->get_pattern_line_tile_count(m_board_index, pattern_line);
			res.emplace_back(position.first, current_fill);
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

const strategy_move& ai::strategy_ai::best_fill(const std::vector<strategy_move>& moves)
{
	int to_fill = moves.begin()->to_fill();
	int least_empty = to_fill;
	const strategy_move* least_empty_move = nullptr;
	int smallest_overflow = moves[0].get_overflow(); // Here 20 is simply the largest possible overflow that could occur in a 2 player game
	const strategy_move* smallest_overflow_move = &moves[0];
	for(auto&& move: moves)
	{
		int move_hole = to_fill - move.get_tile_count();
		int move_overflow = move.get_overflow();
		if(move_hole >= 0 && move_hole < least_empty)
		{
			least_empty = move_hole;
			least_empty_move = &move;
		}
		if(move_overflow < smallest_overflow)
		{
			smallest_overflow = move_overflow;
			smallest_overflow_move = &move;
		}
	}
	if (least_empty_move) return *least_empty_move;
	return *smallest_overflow_move;
	
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
	auto model = m_controller->get_model();
	std::vector<strategy_move> moves = get_moves();
	// Sort moves into groups by tiles on the wall
	std::map<int, std::vector<strategy_move>> sorted_moves = sort_moves(moves);
	// Filling partially filled lines first
	for(int i = model::COLORS - 1; i >= 0; --i)
	{
		model::tile color_i = model->pattern_line_color(m_board_index, i);
		if(color_i != model::tile::empty)
		{
			int index = (((int)color_i + i) % model::COLORS) + i * model::COLORS;
			if (sorted_moves[index].size() > 0) return best_fill(sorted_moves[index]).gen_move();
		}
	}
	// If no pattern line requires filling, pick the pattern line that can be filled the most
	std::vector<std::pair<int, float>> possible_fill = calculate_possible_fill(sorted_moves);
	std::sort(possible_fill.begin(), possible_fill.end(), [](auto a, auto b) {return a.second > b.second; });
	return best_fill(sorted_moves[possible_fill[0].first]).gen_move();
	
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

void ai::strategy_ai::init(std::vector<std::pair<std::string, std::string>> args)
{
}
