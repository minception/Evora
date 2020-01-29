#pragma once
#include <map>
#include "AI.h"

namespace AI
{
	class AIFactory;
	class AIFactory
	{
		static char** ai_names;
	public:

		virtual std::unique_ptr<AI> get(std::shared_ptr<model::game> game) = 0;
		static std::map<const char*, std::unique_ptr<AIFactory>> get_factories();
	};
	class RandomAIFactory :public AIFactory
	{
	public:
		std::unique_ptr<AI> get(std::shared_ptr<model::game> game) override;
	};
}
