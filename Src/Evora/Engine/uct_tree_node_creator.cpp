#include "uct_tree_node_creator.h"
#include "UCTTreeNode.h"

std::shared_ptr<tree_node> uct_tree_node_creator::gen_root_node(const game_state& rootState) const
{
	return std::make_shared<UCTTreeNode>(nullptr, nullptr, rootState, m_constant);
}
