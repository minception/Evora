#include "MonteCarloAI.h"
#include "utils.h"

void AI::MonteCarloAI::move()
{
	std::chrono::system_clock::time_point starting_time = std::chrono::system_clock::now();

	std::chrono::system_clock::time_point end_time = starting_time + std::chrono::milliseconds(m_time);
	while(utils::timeLeft(end_time))
	{
	}
}

const char* AI::MonteCarloAI::get_name() const
{
	return "MonteCarloAI";
}
