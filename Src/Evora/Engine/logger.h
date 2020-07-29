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
		virtual void finish() = 0;
		void set_output(std::string file_name) { m_output_path = file_name; }
	};

	class empty_logger :public logger
	{
	public:
		void init() override{}
		void step(std::shared_ptr<control::game_controller> controller) override{}
		void finish() override{}
	};
	class avg_score_per_round: public logger
	{
	private:
		int m_round;
		int m_repeats;
		std::ofstream m_output;
		std::vector<std::pair<int, int>> m_score_sums;
		bool m_wall_tiling = false;
	public:
		void init() override;
		void step(std::shared_ptr<control::game_controller> controller) override;
		void finish() override;
	};
	
}
