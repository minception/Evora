#pragma once

#include "game_move.h"
#include "game_state.h"
#include <memory>

class tree_node
{
public:
	virtual ~tree_node();
	virtual std::shared_ptr<tree_node> add_child(std::shared_ptr<const game_move> move, std::shared_ptr<tree_node> parent, const game_state& state) = 0;
	virtual std::shared_ptr<const game_move> get_best_move() const = 0;
	virtual bool has_children() const = 0;
	virtual bool has_moves_to_try() const = 0;
	virtual std::shared_ptr<const game_move> get_move() const = 0;
	virtual std::shared_ptr<tree_node> get_parent() const = 0;
	virtual int get_player_who_just_moved() const = 0;
	virtual std::shared_ptr<tree_node> select_child() const = 0;
	virtual std::shared_ptr<const game_move> select_untried_move() const = 0;
	virtual void update(double result) = 0;
};

