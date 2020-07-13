#pragma once

#include "tree_node.h"
#include <random>

class uct_tree_node : public tree_node
{
public:
	uct_tree_node(std::shared_ptr<const game_move> move, std::shared_ptr<uct_tree_node> parent, const game_state& state, double constant = 1.0, bool generateUntriedMoves = true);
	virtual ~uct_tree_node() = default;
	uct_tree_node(const uct_tree_node& src);
	uct_tree_node& operator=(const uct_tree_node& rhs);
	uct_tree_node(uct_tree_node&& src) noexcept;
	uct_tree_node& operator=(uct_tree_node&& rhs) noexcept;

	std::shared_ptr<tree_node> add_child(std::shared_ptr<const game_move> move, std::shared_ptr<tree_node> parent, const game_state& state) override;
	std::shared_ptr<const game_move> get_best_move() const override;
	bool has_children() const override;
	bool has_moves_to_try() const override;
	std::shared_ptr<const game_move> get_move() const override;
	std::shared_ptr<tree_node> get_parent() const override;
	int get_player_who_just_moved() const override;
	std::shared_ptr<tree_node> select_child() const override;
	std::shared_ptr<const game_move> select_untried_move() const override;
	void update(double result) override;
	static int get_nodes_created();

protected:
	std::vector<std::shared_ptr<uct_tree_node>> m_child_nodes;
	std::vector<std::shared_ptr<const game_move>> m_untried_moves;
	int m_visits;
	double m_constant;
private:
	void copy_from(const uct_tree_node& src);
	void free_memory();
	void move_from(const uct_tree_node& src);
	double uct_value() const;

	std::weak_ptr<uct_tree_node> m_parent;
	std::shared_ptr<const game_move> m_move;
	double m_wins;
	int m_player_who_just_moved;
	std::shared_ptr<std::mt19937> m_rng;
	static int nodes_created;
};