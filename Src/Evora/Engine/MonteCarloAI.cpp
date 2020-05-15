#include "MonteCarloAI.h"

#include "AzulGameMove.h"
#include "AzulGameState.h"
#include "center_offer.h"
#include "drop_center.h"
#include "drop_factory.h"
#include "factory_offer.h"
#include "game_controller.h"
#include "UCTTreeNodeCreator.h"
#include "utils.h"

AI::MonteCarloAI::MonteCarloAI(std::shared_ptr<control::game_controller> controller, int board_index, int time) :
	AI(controller, board_index), m_time(time)
{
	m_creator = std::make_unique<UCTTreeNodeCreator>();
	m_mcts = std::make_unique<MCTSAlgorithm>(*m_creator);
}

void AI::MonteCarloAI::move()
{
	std::shared_ptr<control::game_controller> mockup = std::make_shared<control::game_controller>(*m_controller);
	AzulGameState state(mockup, m_board_index);
	auto best_move = m_mcts->Search(state, m_time);
	const AzulGameMove& azulMove = dynamic_cast<const AzulGameMove&>(*best_move);

	m_controller->add_command(azulMove.generateCommand(m_board_index));
	m_controller->step();
}


const char* AI::MonteCarloAI::get_name() const
{
	return "MonteCarloAI";
}
