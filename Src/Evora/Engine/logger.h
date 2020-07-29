#pragma once
#include <memory>
#include<fstream>

#include "game_controller.h"

namespace logging
{
	class logger
	{
	protected:
		std::string m_output_path;
	public:
		virtual void init() = 0;
		virtual void step(std::shared_ptr<control::game_controller> controller) = 0;
		virtual void game_over(std::shared_ptr<control::game_controller> controller) = 0;
		virtual void finish() = 0;
		void set_output(std::string file_name) { m_output_path = file_name; }
	};

	class empty_logger :public logger
	{
	public:
		void init() override{}
		void step(std::shared_ptr<control::game_controller> controller) override{}
		void finish() override{}
		void game_over(std::shared_ptr<control::game_controller> controller) override{};
	};
	class avg_score_per_round: public logger
	{
		int m_round;
		int m_repeats;
		std::ofstream m_output;
		std::vector<std::pair<int, int>> m_score_sums;
		bool m_wall_tiling = false;
	public:
		void init() override;
		void step(std::shared_ptr<control::game_controller> controller) override;
		void finish() override;
		void game_over(std::shared_ptr<control::game_controller> controller) override{};
	};
	class win_percentage: public logger
	{
		int m_plays = 0;
		int m_wins = 0;
	public:
		void init() override{};
		void step(std::shared_ptr<control::game_controller> controller) override{};
		void game_over(std::shared_ptr<control::game_controller> controller) override;
		void finish() override;
	};
	
}
