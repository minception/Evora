#pragma once
#include <map>
#include <cstring>
#include "AI.h"

namespace AI
{
	struct RawPointerComparison
	{
		bool operator()(char const* lhs, char const* rhs) const
		{
			return strcmp(lhs, rhs) < 0;
		}
	};
	
	/**
	 * \brief A factory class for creating AI instances
	 */
	class AIFactory
	{
		static char** ai_names;
	public:

		virtual std::unique_ptr<AI> get(std::shared_ptr<control::game_controller> controller, int player_index) = 0;
		static std::map<const char*, std::unique_ptr<AIFactory>, RawPointerComparison> get_factories();
	};
	class RandomAIFactory :public AIFactory
	{
	public:
		std::unique_ptr<AI> get(std::shared_ptr<control::game_controller> controller, int player_index) override;
	};
	class GreedyAIFactory :public AIFactory
	{
	public:
		std::unique_ptr<AI> get(std::shared_ptr<control::game_controller> controller, int player_index) override;
	};
}
