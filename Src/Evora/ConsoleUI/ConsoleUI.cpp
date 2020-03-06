// ConsoleUI is a testing environment for the engine
//

#include <iostream>
#include "game.h"
#include "game_controller.h"
#include "AI.h"
#include "AIFactory.h"
#include <string>
#include <chrono>


int main(int argc, const char** argv)
{
	if(argc == 4)
	{
		std::vector<std::string> arg_list(argv + 1, argv + argc);
		auto ai_factories = AI::AIFactory::get_factories();
		std::string AI1name = arg_list[0];
		std::string AI2name = arg_list[1];
		if (!ai_factories.count(AI1name.c_str()))
		{
			std::cout << "Unknown AI " << AI1name << std::endl;
			return 1;
		}
		if(!ai_factories.count(AI2name.c_str()))
		{
			std::cout << "Unknown AI " << AI2name << std::endl;
			return 1;
		}
		int number_of_games = std::stoi(arg_list[2]);
		std::vector<int> wins{ 0,0 };

		auto start = std::chrono::high_resolution_clock::now();
		
		for(int i = 0; i < number_of_games; ++i)
		{
			std::shared_ptr<control::game_controller> controller = std::make_shared<control::game_controller>(std::make_shared<model::game>(2));
			controller->start_game();
			int current_player = 0;
			controller->set_first_player(current_player);
			std::vector<std::unique_ptr<AI::AI>> players;
			players.push_back(ai_factories.at(AI1name.c_str())->get(controller, 0));
			players.push_back(ai_factories.at(AI2name.c_str())->get(controller, 1));
			bool round_over = false;
			while(true)
			{
				if(!controller->step())
				{
					if(controller->game_over())
					{
						int winner = controller->get_winner();
						wins[winner]++;
						std::cout << "Player " << players[winner]->get_name() << " won game number " << i << std::endl;
						break;
					}
					if(round_over)
					{
						current_player = controller->get_first_player();
						round_over = false;
					}
					players[current_player]->move();
					current_player = (current_player + 1) % 2;
				}
				else if(!round_over && controller->is_round_over())
				{
					round_over = true;
				}
			}
		}

		auto finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time: " << elapsed.count() << std::endl;
		
		std::cout << "Player " << AI1name << " won " << wins[0] << " out of " << number_of_games << " games. Win rate: " << wins[0] / (float)number_of_games * 100 << "%" << std::endl;
		std::cout << "Player " << AI2name << " won " << wins[1] << " out of " << number_of_games << " games. Win rate: " << wins[1] / (float)number_of_games * 100 << "%" << std::endl;
	}
	else
	{
		std::cout << "Usage : evora <AI name> <AI name> <number of games>" << std::endl;
	}
    return 0;
}

