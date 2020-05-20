#include "mcts_algorithm.h"
#include "utils.h"
#include <chrono>

void mcts_algorithm::do_iteration(const game_state& root_state, std::shared_ptr<tree_node> root_node)
{
	std::shared_ptr<tree_node> node = root_node;
	std::shared_ptr<game_state> state = root_state.clone();

	// Select
	while (!node->has_moves_to_try() && node->has_children()) {
		node = node->select_child();
		state->do_move(*node->get_move());
	}

	// Expand
	if (node->has_moves_to_try()) {
		std::shared_ptr<const game_move> move = node->select_untried_move();
		state->do_move(*move);
		node = node->add_child(move, node, *state);
	}

	// Rollout
	while (!state->is_terminal()) {
		state->do_move(state->get_simulation_move());
	}

	// Backpropagate
	while (node != nullptr) {
		node->update(state->get_result(node->get_player_who_just_moved()));
		node = node->get_parent();
	}
}

std::shared_ptr<const game_move> mcts_algorithm::search(const game_state& root_state, int time)
{
	auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(time);

	if (!m_b_search) {
		m_b_search = true;
	}

	m_last_iterations = 0;

	std::shared_ptr<tree_node> rootNode = m_tree_creator.gen_root_node(root_state);
	while (true)
	{
		++m_last_iterations;

		do_iteration(root_state, rootNode);

		if (!utils::time_left(end_time))
		{
			break;
		}

		if (!m_b_search)
		{
			m_b_search = true;
			break;
		}
	}

	return rootNode->get_best_move();
}

const tree_node_creator& mcts_algorithm::get_tree_creator() const
{
	return m_tree_creator;
}

int mcts_algorithm::get_last_iterations() const
{
	return m_last_iterations;
}

void mcts_algorithm::abort()
{
	m_b_search = false;
}

mcts_algorithm::~mcts_algorithm()
{
}
