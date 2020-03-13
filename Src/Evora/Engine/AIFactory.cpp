#include "AIFactory.h"

#include "GreedyAI.h"
#include "MinimaxAI.h"
#include "MonteCarloAI.h"
#include "RandomAI.h"
#include "StrategyAI.h"

using namespace AI;


std::map<const char*, std::unique_ptr<AIFactory>, RawPointerComparison> AIFactory::get_factories()
{
	std::map < const char*, std::unique_ptr<AIFactory>, RawPointerComparison> res;
	res.insert({ "RandomAI", std::move(std::make_unique<RandomAIFactory>()) });
	res.insert({ "GreedyAI", std::move(std::make_unique<GreedyAIFactory>()) });
	res.insert({ "MinimaxAI", std::move(std::make_unique<MinimaxAIFactory>()) });
	res.insert({ "StrategyAI", std::move(std::make_unique<StrategyAIFactory>()) });
	res.insert({ "MonteCarloAI", std::move(std::make_unique<MonteCarloAIFactory>()) });
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

std::unique_ptr<::AI::AI> StrategyAIFactory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<StrategyAI>(controller, board_index));
}

std::unique_ptr<::AI::AI> MonteCarloAIFactory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<MonteCarloAI>(controller, board_index));
}
