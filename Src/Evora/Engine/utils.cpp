#include "utils.h"

namespace utils
{
	int play_game(std::vector<std::unique_ptr<AI::AI>>& players, std::shared_ptr<control::game_controller> controller, int current_player)
	{
		bool round_over = false;
		while (true)
		{
			if (!controller->step())
			{
				if (controller->game_over())
				{
					return controller->get_winner();
				}
				if (round_over)
				{
					current_player = controller->get_first_player();
					round_over = false;
				}
				players[current_player]->move();
				current_player = (current_player + 1) % 2;
			}
			else if (!round_over && controller->is_round_over())
			{
				round_over = true;
			}
		}
	}
	int evaluate(std::shared_ptr<control::game_controller>& controller, int player_index)
	{
		int moves = controller->add_wall_tiling_faze();
		for (int i = 0; i < moves; ++i)
		{
			controller->step();
		}
		int score = 0;
		for (int player_index = 0; player_index < controller->get_model()->player_count(); ++player_index)
		{
			if (player_index == player_index)
			{
				score += controller->get_score(player_index);
			}
			else
			{
				score -= controller->get_score(player_index);
			}
		}
		for (int i = 0; i < moves; ++i)
		{
			controller->step_back();
		}
		return score;
	}
}

