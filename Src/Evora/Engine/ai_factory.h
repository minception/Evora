#pragma once
#include <map>
#include <cstring>
#include "ai.h"

namespace ai
{
	struct raw_pointer_comparison
	{
		bool operator()(char const* lhs, char const* rhs) const
		{
			return strcmp(lhs, rhs) < 0;
		}
	};
	
	/**
	 * \brief A factory class for creating ai instances
	 */
	class ai_factory
	{
		static char** ai_names;
	public:
		virtual ~ai_factory() = default;

		virtual std::unique_ptr<ai> get(std::shared_ptr<control::game_controller> controller, int player_index) = 0;
		static std::map<const char*, std::unique_ptr<ai_factory>, raw_pointer_comparison> get_factories();
	};
	
	class random_ai_factory :public ai_factory
	{
	public:
		std::unique_ptr<ai> get(std::shared_ptr<control::game_controller> controller, int board_index) override;
	};
	
	class greedy_ai_factory :public ai_factory
	{
	public:
		std::unique_ptr<ai> get(std::shared_ptr<control::game_controller> controller, int board_index) override;
	};

	class minimax_ai_factory :public ai_factory
	{
	public:
		std::unique_ptr<ai> get(std::shared_ptr<control::game_controller> controller, int board_index) override;
	};

	class strategy_ai_factory :public ai_factory
	{
	public:
		std::unique_ptr<ai> get(std::shared_ptr<control::game_controller> controller, int board_index) override;
	};

	class monte_carlo_ai_factory :public ai_factory
	{
	public:
		std::unique_ptr<ai> get(std::shared_ptr<control::game_controller> controller, int board_index) override;
	};
}
