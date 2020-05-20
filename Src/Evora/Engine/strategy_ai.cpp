#include "strategy_ai.h"
#include "utils.h"
#include "center_offer.h"
#include "drop_center.h"
#include "factory_offer.h"

void ai::strategy_ai::move()
{
	std::vector<std::unique_ptr<control::command>> moves = m_controller->get_possible_moves(m_board_index);
	int to_execute = 0;
	int max_move_score = std::numeric_limits<int>::min();
	std::vector<std::unique_ptr<control::command>> positive_commands;
	std::vector<std::unique_ptr<control::command>> negative_commands;
	

	std::vector<model::tile> center_colors = m_controller->get_model()->get_center_colors();
	for (auto&& color : center_colors)
	{
		for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
		{
			if (m_controller->get_model()->can_add_to_pattern_line(m_board_index, pattern_line_index, color))
			{
				positive_commands.emplace_back(std::make_unique<control::center_offer>(m_board_index, pattern_line_index, color));
			}
		}
		// for every color adding move to floor
		negative_commands.emplace_back(std::make_unique<control::drop_center>(m_board_index, color));
	}

	for (int factory_index = 0; factory_index < m_controller->get_model()->factory_count(); ++factory_index)
	{
		std::vector<model::tile> colors = m_controller->get_model()->get_factory_colors(factory_index);
		for (auto&& color : colors)
		{
			for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
			{
				if (m_controller->get_model()->can_add_to_pattern_line(m_board_index, pattern_line_index, color))
				{
					positive_commands.emplace_back(std::make_unique<control::factory_offer>(m_board_index, factory_index, pattern_line_index, color));
				}
			}
			// for every color adding move to floor
			negative_commands.emplace_back(std::make_unique<control::drop_center>(m_board_index, color));
		}
	}
	m_controller->add_command(std::move(moves[to_execute]));
	m_controller->step();
}

const char* ai::strategy_ai::get_name() const
{
	return "StrategyAI";
}
