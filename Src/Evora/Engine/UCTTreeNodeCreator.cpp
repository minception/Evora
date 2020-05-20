#include "UCTTreeNodeCreator.h"
#include "UCTTreeNode.h"

std::shared_ptr<TreeNode> UCTTreeNodeCreator::GenRootNode(const GameState& rootState) const
{
	return std::make_shared<UCTTreeNode>(nullptr, nullptr, rootState, mConstant);
}