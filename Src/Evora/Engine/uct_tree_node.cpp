#include "uct_tree_node.h"
#include <memory>
#include <algorithm>
#include <iostream>

int uct_tree_node::nodes_created = 0;

uct_tree_node::uct_tree_node(std::shared_ptr<const game_move> move, std::shared_ptr<uct_tree_node> parent,
                         const game_state& state, double constant, bool generateUntriedMoves)
	:m_move(move), m_parent(parent), m_constant(constant), m_wins(0), m_visits(0)
{
	nodes_created++;
	m_player_who_just_moved = state.get_player_who_just_moved();
	if(generateUntriedMoves)
	{
		m_untried_moves = state.get_moves();
	}
	m_rng = state.get_rng();
}

uct_tree_node::uct_tree_node(const uct_tree_node& src)
{
	copy_from(src);
}

uct_tree_node& uct_tree_node::operator=(const uct_tree_node& rhs)
{
	// Check for self-assignment
	if (this != &rhs)
	{
		free_memory();
		copy_from(rhs);
	}
	return *this;
}

uct_tree_node::uct_tree_node(uct_tree_node&& src) noexcept
{
	move_from(src);
}

uct_tree_node& uct_tree_node::operator=(uct_tree_node&& rhs) noexcept
{
	if (this!= &rhs)
	{
		move_from(rhs);
	}
	return *this;
}

std::shared_ptr<tree_node> uct_tree_node::add_child(std::shared_ptr<const game_move> move, std::shared_ptr<tree_node> parent, const game_state& state)
{
	std::shared_ptr<uct_tree_node> node = std::make_shared<uct_tree_node>(move, std::dynamic_pointer_cast<uct_tree_node>(parent), state, m_constant);
	m_untried_moves.erase(std::remove(m_untried_moves.begin(), m_untried_moves.end(), move), m_untried_moves.end());
	m_child_nodes.push_back(node);
	return node;
}

std::shared_ptr<const game_move> uct_tree_node::get_best_move() const
{
	std::vector<std::shared_ptr<uct_tree_node>> sortedChildNodes(m_child_nodes);
	std::sort(sortedChildNodes.begin(), sortedChildNodes.end(), [](std::shared_ptr<uct_tree_node> x, std::shared_ptr<uct_tree_node> y) {return (float)x->m_wins / x->m_visits > (float)y->m_wins / y->m_visits; });
	//print_best_moves(sortedChildNodes);
	return sortedChildNodes[0]->m_move;
}

bool uct_tree_node::has_children() const
{
	return !m_child_nodes.empty();
}

bool uct_tree_node::has_moves_to_try() const
{
	return !m_untried_moves.empty();
}

int uct_tree_node::get_player_who_just_moved() const
{
	return m_player_who_just_moved;
}

std::shared_ptr<tree_node> uct_tree_node::get_parent() const
{
	return m_parent.lock();
}

std::shared_ptr<const game_move> uct_tree_node::get_move() const
{
	return m_move;
}

std::shared_ptr<tree_node> uct_tree_node::select_child() const
{
	std::vector<std::shared_ptr<uct_tree_node>> sortedChildNodes(m_child_nodes);
	sort(sortedChildNodes.begin(), sortedChildNodes.end(), [](std::shared_ptr<uct_tree_node> x, std::shared_ptr<uct_tree_node> y) {return x->uct_value() > y->uct_value(); });
	return sortedChildNodes[0];
}

std::shared_ptr<const game_move> uct_tree_node::select_untried_move() const
{
	std::uniform_int_distribution<int> dist(0, m_untried_moves.size() - 1);
	int random_number = dist(*m_rng);
	return m_untried_moves[random_number];
}

void uct_tree_node::copy_from(const uct_tree_node& src)
{
	for(auto& child: src.m_child_nodes)
	{
		m_child_nodes.push_back(std::make_shared <uct_tree_node> (*child));
	}
	m_untried_moves = src.m_untried_moves;
	m_visits = src.m_visits;
	m_constant = src.m_constant;
	m_move = src.m_move;
	m_wins = src.m_wins;
	m_player_who_just_moved = src.m_player_who_just_moved;
	m_rng = src.m_rng;
}

void uct_tree_node::free_memory()
{
	m_child_nodes.clear();
	m_parent.reset();
}

void uct_tree_node::move_from(const uct_tree_node& src)
{
	m_child_nodes = std::move(m_child_nodes);
	m_untried_moves = std::move(src.m_untried_moves);
	m_visits = std::move(src.m_visits);
	m_constant = std::move(src.m_constant);
	m_move = std::move(src.m_move);
	m_wins = std::move(src.m_wins);
	m_player_who_just_moved = std::move(src.m_player_who_just_moved);
	m_rng = std::move(src.m_rng);
}

void uct_tree_node::update(double result)
{
	++m_visits;
	m_wins += result;
}

int uct_tree_node::get_nodes_created()
{
	int res = nodes_created;
	nodes_created = 0;
	return res;

}

double uct_tree_node::uct_value() const
{
	auto parent = m_parent.lock();
	return m_wins / m_visits + m_constant * sqrt(2 * log(parent->m_visits) / m_visits) + progressive_bias();
}

double uct_tree_node::progressive_bias() const
{
	return m_move->get_value() / (m_visits + 1);
}

void uct_tree_node::print_best_moves(std::vector<std::shared_ptr<uct_tree_node>> sorted_nodes) const
{
	std::cout << "Best moves:" << std::endl;
	for (int i = 0; i < 10; ++i) {
		if (i == sorted_nodes.size()) break;
		std::cout << i + 1 << ". " << sorted_nodes[i]->m_move->to_string() << "\n\tGames won " << sorted_nodes[i]->m_wins << "/" << sorted_nodes[i]->m_visits << std::endl;
	}
}


