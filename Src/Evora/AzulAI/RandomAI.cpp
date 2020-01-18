#include "RandomAI.h"

namespace AI
{
	void RandomAI::move()
	{
	}

	RandomAI::RandomAI(std::shared_ptr<model::game> model) : AI(model)
	{
		std::random_device seed;
		m_rng = std::mt19937{ seed() };
	}
}
	
