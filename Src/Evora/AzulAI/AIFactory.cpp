#include "AIFactory.h"
#include "RandomAI.h"

using namespace AI;


std::map<const char*, std::unique_ptr<AIFactory>> AIFactory::get_factories()
{
	std::map<const char*, std::unique_ptr<AIFactory>> res;
	res.insert({ "RandomAI", std::move(std::make_unique<RandomAIFactory>()) });
	return res;
}

std::unique_ptr<::AI::AI> RandomAIFactory::get(std::shared_ptr<model::game> game)
{
	return std::move(std::make_unique<RandomAI>(game));
}
