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
}
