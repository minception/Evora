#include "ai_factory.h"

#include "ad_ai.h"
#include "greedy_ai.h"
#include "minimax_ai.h"
#include "monte_carlo_ai.h"
#include "random_ai.h"
#include "strategy_ai.h"

using namespace ai;


std::map<const char*, std::unique_ptr<ai_factory>, raw_pointer_comparison> ai_factory::get_factories()
{
	std::map < const char*, std::unique_ptr<ai_factory>, raw_pointer_comparison> res;
	res.insert({ "RandomAI", std::move(std::make_unique<random_ai_factory>()) });
	res.insert({ "GreedyAI", std::move(std::make_unique<greedy_ai_factory>()) });
	res.insert({ "MinimaxAI", std::move(std::make_unique<minimax_ai_factory>()) });
	res.insert({ "StrategyAI", std::move(std::make_unique<strategy_ai_factory>()) });
	res.insert({ "MonteCarloAI", std::move(std::make_unique<monte_carlo_ai_factory>()) });
	res.insert({ "AD_AI", std::move(std::make_unique<ad_ai_factory>()) });
	return res;
}

std::unique_ptr<::ai::ai> random_ai_factory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<random_ai>(controller, board_index));
}

std::unique_ptr<::ai::ai> greedy_ai_factory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<greedy_ai>(controller, board_index));
}

std::unique_ptr<::ai::ai> minimax_ai_factory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<minimax_ai>(controller, board_index));
}

std::unique_ptr<::ai::ai> strategy_ai_factory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<strategy_ai>(controller, board_index));
}

std::unique_ptr<::ai::ai> monte_carlo_ai_factory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<monte_carlo_ai>(controller, board_index));
}

std::unique_ptr<::ai::ai> ad_ai_factory::get(std::shared_ptr<control::game_controller> controller, int board_index)
{
	return std::move(std::make_unique<ad_ai>(controller, board_index));
}
