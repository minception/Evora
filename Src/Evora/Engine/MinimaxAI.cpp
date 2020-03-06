#include "MinimaxAI.h"
#include <stack>

int AI::MinimaxAI::evaluate_move(int player_index, int depth, std::shared_ptr<control::game_controller> controller)
{
	std::shared_ptr<model::game> game = controller->get_model();
	std::vector<model::tile> center_colors = game->get_center_colors();

	// all center to pattern line moves
	for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
	{
		for (auto&& color : center_colors)
		{
			if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
			{
				//commands.push_back(std::move(std::make_unique<center_offer>(player_index, pattern_line_index, color)));
			}
		}
	}
	// all center to floor moves
	for (auto&& color : center_colors)
	{
		//commands.push_back(std::move(std::make_unique<drop_center>(player_index, color)));
	}
	for (int factory_index = 0; factory_index < game->factory_count(); ++factory_index)
	{
		std::vector<model::tile> factory_colors = game->get_factory_colors(factory_index);
		//all factory to pattern line moves
		for (int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
		{
			for (auto&& color : factory_colors)
			{
				if (game->can_add_to_pattern_line(player_index, pattern_line_index, color))
				{
					//commands.push_back(std::move(std::make_unique<factory_offer>(factory_index, player_index, pattern_line_index, color)));
				}
			}
		}
		// all factory to floor moves
		for (auto&& color : factory_colors)
		{
			//commands.push_back(std::move(std::make_unique<drop_factory>(factory_index, player_index, color)));
		}
	}
	return 0;
}

void AI::MinimaxAI::move()
{
	std::vector<std::unique_ptr<control::command>> moves = m_controller->get_possible_moves(m_board_index);
	int to_execute = 0;
	int max_move_score = std::numeric_limits<int>::min();
	control::game_controller mockup{ *m_controller };
	for (int i = 0; i < moves.size(); ++i)
	{
		mockup.add_command(std::move(moves[i]->clone()));
		mockup.step();
		int move_score = mockup.evaluate_state(m_board_index);
		if (move_score > max_move_score)
		{
			max_move_score = move_score;
			to_execute = i;
		}
		mockup.step_back();
	}
	m_controller->add_command(std::move(moves[to_execute]));
	m_controller->step();
}

const char* AI::MinimaxAI::get_name() const
{
	return "MinimaxAI";
}
