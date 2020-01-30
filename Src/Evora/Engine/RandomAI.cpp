#include "RandomAI.h"

namespace AI
{
	void RandomAI::move()
	{
	}

	RandomAI::RandomAI(std::shared_ptr<control::game_controller> controller) : AI(controller)
	{
		std::random_device seed;
		m_rng = std::mt19937{ seed() };
	}

	const char* RandomAI::get_name() const
	{
		return "RandomAI";
	}
}
	
