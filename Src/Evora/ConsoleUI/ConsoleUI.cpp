// ConsoleUI is a testing environment for the engine
//

#include <chrono>
#include <iostream>
#include <string>
#include <cmath>

#include "ai.h"
#include "ai_factory.h"
#include "game.h"
#include "game_controller.h"
#include "utils.h"
#include <numeric>
#include "ConsoleUI.h"

void display_usage()
{
	std::cout << "Usage : evora <ai name> <ai name> <number of games>" << std::endl;
	std::cout << "Available AIs:" << std::endl;
	auto ai_factories = ai::ai_factory::get_factories();
	for (auto&& ai_factory : ai_factories)
	{
		std::cout << '\t' << ai_factory.first << std::endl;
	}
}

void display_player_stats(std::string name, int wins, int games_played)
{

	float win_ratio = wins / (float)games_played;

	float standard_deviation = sqrt((1 - win_ratio) * win_ratio * win_ratio + (win_ratio) * (1 - win_ratio) * (1 - win_ratio));

	float confidence = 95;
	float z = 1.960;
	float interval_delta = z * (standard_deviation / sqrt(games_played));

	std::cout << "Player " << name << " won " << wins << " out of " << games_played << " games. Win rate: " << win_ratio * 100 << "%" << std::endl;
	std::cout << "With confidence " << confidence << " % " << win_ratio - interval_delta << " < p < " << win_ratio + interval_delta << std::endl;
}

void display_score_stats(const std::vector<int>& score_delta)
{
	float mean = std::accumulate(score_delta.begin(), score_delta.end(), 0) / (float)score_delta.size();

	if (mean > 0)
	{
		std::cout << "On average, player 1 won by " << mean << std::endl;
	}
	else if (mean < 0)
	{
		std::cout << "On average, player 2 won by " << -mean << std::endl;
	}
	else
	{
		std::cout << "On average, players had the same score" << std::endl;
	}

	float temp = 0;
	for (auto&& delta : score_delta)
	{
		temp += pow(delta - mean, 2);
	}
	float standard_deviation = sqrt(temp / (score_delta.size() - 1));
	std::cout << "Score difference standard deviation is " << standard_deviation << std::endl;

	float confidence = 95;
	float z = 1.960;
	float confidence_interval_delta = z * (standard_deviation / sqrt(score_delta.size()));;
	std::cout << "With confidence " << confidence << " %  the score difference is between " << abs(mean) - confidence_interval_delta << " and " << abs(mean) + confidence_interval_delta;
}

bool parse_args(const std::vector<std::basic_string<char>>& arg_list, std::string& ai1_name, std::string& ai2_name,
                std::vector<std::pair<std::basic_string<char>, std::basic_string<char>>>& ai1_args,
                std::vector<std::pair<std::basic_string<char>, std::basic_string<char>>>& ai2_args,
				int& number_of_games)
{
	try
	{
		int index = 0;
		ai1_name = arg_list[index++];
		while (true)
		{
			auto delim_pos = arg_list[index].find("=");
			if (delim_pos == std::string::npos) break;
			ai1_args.emplace_back(arg_list[index].substr(0, delim_pos), arg_list[index].substr(delim_pos + 1, arg_list[index].size()));
			index++;
		}
		ai2_name = arg_list[index++];
		while (true)
		{
			auto delim_pos = arg_list[index].find("=");
			if (delim_pos == std::string::npos) break;
			ai2_args.emplace_back(arg_list[index].substr(delim_pos), arg_list[index].substr(delim_pos + 1, arg_list[index].size()));
			index++;
		}
		number_of_games = std::stoi(arg_list[index]);
		if(index == arg_list.size() - 1)
		{
			return true;
		}
		return false;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

int main(int argc, const char** argv)
{
	std::vector<std::string> arg_list(argv + 1, argv + argc);
	auto ai_factories = ai::ai_factory::get_factories();
	std::string AI1name, AI2name;
	std::vector<std::pair<std::string, std::string>> AI1args, AI2args;
	int number_of_games;
	if (parse_args(arg_list, AI1name, AI2name, AI1args, AI2args, number_of_games)) {


		if (!ai_factories.count(AI1name.c_str()))
		{
			std::cout << "Unknown ai " << AI1name << std::endl;
			display_usage();
			return 1;
		}
		if (!ai_factories.count(AI2name.c_str()))
		{
			std::cout << "Unknown ai " << AI2name << std::endl;
			display_usage();
			return 1;
		}
		std::vector<int> wins{ 0,0 };
		std::vector<int> score_delta;

		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < number_of_games; ++i)
		{
			std::shared_ptr<control::game_controller> controller = std::make_shared<control::game_controller>(std::make_shared<model::game>(2, i));
			int current_player = 0;
			controller->start_game(current_player);
			std::vector<std::unique_ptr<ai::ai>> players;
			players.push_back(ai_factories.at(AI1name.c_str())->get(controller, 0));
			players[0]->init(AI1args);
			players.push_back(ai_factories.at(AI2name.c_str())->get(controller, 1));
			players[1]->init(AI2args);
			int winner = utils::play_game(players, controller, current_player);
			wins[winner]++;
			std::cout << "Player " << winner + 1 << " : " << players[winner]->get_name() << " won game number " << i << std::endl;
			std::cout << "Score: " << controller->get_score(0) << ":" << controller->get_score(1) << std::endl;
			score_delta.push_back(controller->get_score(0) - controller->get_score(1));
		}

		auto finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time: " << elapsed.count() << std::endl;

		display_player_stats(AI1name, wins[0], number_of_games);
		display_player_stats(AI2name, wins[1], number_of_games);
		display_score_stats(score_delta);
	}
	else {
		display_usage();
	}
	return 0;
}




