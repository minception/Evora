#pragma once

#include "tree_node.h"

class tree_node_creator
{
public:
	virtual ~tree_node_creator();
	virtual std::shared_ptr<tree_node> gen_root_node(const game_state& rootState) const = 0;
};

