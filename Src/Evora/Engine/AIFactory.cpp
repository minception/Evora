#include "AIFactory.h"
#include "RandomAI.h"
#include "GreedyAI.h"
#include "MinimaxAI.h"

using namespace AI;


std::map<const char*, std::unique_ptr<AIFactory>, RawPointerComparison> AIFactory::get_factories()
{
	std::map < const char*, std::unique_ptr<AIFactory>, RawPointerComparison> res;
	res.insert({ "RandomAI", std::move(std::make_unique<RandomAIFactory>()) });
	res.insert({ "GreedyAI", std::move(std::make_unique<GreedyAIFactory>()) });
	res.insert({ "MinimaxAI", std::move(std::make_unique<MinimaxAIFactory>()) });
	return res;
}

std::unique_ptr<::AI::AI> RandomAIFactory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<RandomAI>(controller, board_index));
}

std::unique_ptr<::AI::AI> GreedyAIFactory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<GreedyAI>(controller, board_index));
}

std::unique_ptr<::AI::AI> MinimaxAIFactory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<MinimaxAI>(controller, board_index));
}
