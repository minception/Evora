#include "logger.h"

void logging::avg_score_per_round::init()
{
	++m_repeats;
	m_round = 0;
}

void logging::avg_score_per_round::step(std::shared_ptr<control::game_controller> controller)
{
	if(controller->is_round_over())
	{
		m_wall_tiling = true;
	}
	else if(m_wall_tiling)
	{
		
		if(m_score_sums.size() == m_round)
		{
			m_score_sums.emplace_back(1, controller->get_score(0));
		}
		else
		{
			m_score_sums[m_round].first++;
			m_score_sums[m_round].second += controller->get_score(0);
		}
		m_round++;
		m_wall_tiling = false;
	}
}

void logging::avg_score_per_round::finish()
{
	m_output.open(m_output_path, std::ios_base::app);
	m_output << "0 0" << std::endl;
	int round = 1;
	for (auto && score_sum : m_score_sums)
	{
		m_output << round << " " << (float)score_sum.second / score_sum.first << std::endl;
		++round;
	}
	m_output.close();
}

void logging::win_percentage::game_over(std::shared_ptr<control::game_controller> controller)
{
	if(controller->get_winner() == 0)
	{
		m_wins++;
	}
	m_plays++;
}

void logging::win_percentage::finish()
{
	std::ofstream output(m_output_path, std::ios_base::app);
	output << (float)m_wins/m_plays * 100 << std::endl;
}

