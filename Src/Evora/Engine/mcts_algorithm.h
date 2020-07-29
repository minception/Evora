#pragma once

#include "tree_node_creator.h"

class mcts_algorithm
{
public:
	mcts_algorithm(const tree_node_creator& treeCreator):m_tree_creator(treeCreator), m_b_search(true), m_last_iterations(0){}
	virtual ~mcts_algorithm();
	mcts_algorithm& operator=(const mcts_algorithm& rhs) = delete;
	mcts_algorithm(mcts_algorithm&& rhs) noexcept = delete;
	mcts_algorithm& operator=(mcts_algorithm&& rhs) noexcept = delete;

	std::shared_ptr<const game_move> search(const game_state& root_state, int time);
	void abort();
	const tree_node_creator& get_tree_creator() const;
	int get_last_iterations() const;
	static void set_heavy_playouts(bool value) { m_heavy_playouts = value; }
private:
	const tree_node_creator& m_tree_creator;
	bool m_b_search;
	static bool m_heavy_playouts;
	int m_last_iterations;
	static void do_iteration(const game_state& root_state, std::shared_ptr<tree_node> root_node);
};
