// ConsoleUI is a testing environment for the engine
//

#include <iostream>
#include "game.h"
#include "game_controller.h"
#include "AI.h"
#include "AIFactory.h"
#include <string>


int main(int argc, const char** argv)
{
	if(argc == 4)
	{
		std::vector<std::string> arg_list(argv + 1, argv + argc);
		control::game_controller controller(std::make_shared<model::game>(2));
		controller.start_game();
		auto ai_factories = AI::AIFactory::get_factories();
		std::string AI1name = arg_list[0];
		std::string AI2name = arg_list[1];
		std::vector<std::unique_ptr<AI::AI>> players;
		players.push_back(ai_factories.at(AI1name.c_str())->get(std::make_shared<control::game_controller>(controller), 0));
		players.push_back(ai_factories.at(AI2name.c_str())->get(std::make_shared<control::game_controller>(controller), 1));
		int number_of_games = std::stoi(arg_list[2]);
		int current_player = 0;
		std::vector<int> wins{ 0,0 };
		for(int i = 0; i < number_of_games; ++i)
		{
			while(true)
			{
				if(!controller.step())
				{
					if(controller.game_over())
					{
						int winner = controller.get_winner();
						wins[winner]++;
						break;
					}
					players[current_player]->move();
					current_player = (current_player + 1) % 2;
				}
			}
		}
		
	}
	else
	{
		std::cout << "Usage : evora <AI name> <AI name> <number of games>" << std::endl;
	}
    return 0;
}

