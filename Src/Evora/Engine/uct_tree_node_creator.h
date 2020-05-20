#pragma once
#include "tree_node_creator.h"

class uct_tree_node_creator :public tree_node_creator
{
public:
	uct_tree_node_creator(float constant = 1.0f): m_constant(constant){}
	virtual ~uct_tree_node_creator() = default;
	std::shared_ptr<tree_node> gen_root_node(const game_state& rootState) const override;
private:
	float m_constant;
};