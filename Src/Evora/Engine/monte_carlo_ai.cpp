#include "monte_carlo_ai.h"

#include <string>

#include "azul_game_move.h"
#include "azul_game_state.h"
#include "drop_factory.h"
#include "game_controller.h"
#include "uct_tree_node_creator.h"
#include "utils.h"

#define COUNTNODES 0

ai::monte_carlo_ai::monte_carlo_ai(std::shared_ptr<control::game_controller> controller, int board_index, int iterations, int time) :
	ai(controller, board_index), m_iterations(iterations), m_time(time)
{
	m_creator = std::make_unique<uct_tree_node_creator>(0.2);
	m_mcts = std::make_unique<mcts_algorithm>(*m_creator);
}

void ai::monte_carlo_ai::move()
{
	std::shared_ptr<control::game_controller> mockup = std::make_shared<control::game_controller>(*m_controller);
	azul_game_state state(mockup, m_board_index);
	auto best_move = m_mcts->search(state, m_iterations, m_time);
	const azul_game_move& azulMove = dynamic_cast<const azul_game_move&>(*best_move);

#if COUNTNODES
	std::cout << "Nodes created in " << m_iterations << " ms: " << uct_tree_node::get_nodes_created() << std::endl;
#endif
	m_controller->add_command(azulMove.generate_command(m_board_index));
	m_controller->step();

}


const char* ai::monte_carlo_ai::get_name() const
{
	return "MonteCarloAI";
}

bool ai::monte_carlo_ai::init(std::vector<std::pair<std::string, std::string>> args)
{
	for (auto && arg : args)
	{
		if(arg.first == "iterations")
		{
			m_iterations = std::stoi(arg.second);
		}
		if(arg.first == "time")
		{
			m_time = std::stoi(arg.second);
		}
		else if(arg.first == "constant")
		{
			m_creator = std::make_unique<uct_tree_node_creator>(std::stof(arg.second));
			m_mcts = std::make_unique<mcts_algorithm>(*m_creator);
		}
		else if(arg.first == "heavy_playouts")
		{
			if(arg.second == "true")
			{
				m_mcts->set_heavy_playouts(true);
			}
			else
			{
				m_mcts->set_heavy_playouts(false);
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}
