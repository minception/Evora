#include "MonteCarloAI.h"
#include "AzulGameState.h"
#include "game_controller.h"
#include "utils.h"
#include "UCTTreeNodeCreator.h"

AI::MonteCarloAI::MonteCarloAI(std::shared_ptr<control::game_controller> controller, int board_index, int time) :
	AI(controller, board_index), m_time(time), m_mcts(UCTTreeNodeCreator())
{
}

void AI::MonteCarloAI::move()
{
	std::shared_ptr<control::game_controller> mockup = std::make_shared<control::game_controller>(*m_controller);
	AzulGameState state(mockup, m_board_index);
	m_mcts.Search(state, m_time);
}

const char* AI::MonteCarloAI::get_name() const
{
	return "MonteCarloAI";
}
