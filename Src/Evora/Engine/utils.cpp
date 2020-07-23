#include "utils.h"

#include "drop_factory.h"

namespace utils
{
	int play_game(std::vector<std::unique_ptr<ai::ai>>& players, std::shared_ptr<control::game_controller> controller, int current_player)
	{
		int move_counter = 0;
		while (true)
		{
			if (!controller->step())
			{
				if (controller->game_over())
				{
					return controller->get_winner();
				}
				current_player = controller->get_current_player();
				players[current_player]->move();
				++move_counter;
			}
		}
	}

	bool time_left(std::chrono::system_clock::time_point end_time)
	{
		return std::chrono::system_clock::now() < end_time;
	}
}

