#pragma once

#include "TreeNode.h"

class TreeNodeCreator
{
public:
	virtual ~TreeNodeCreator() = 0;
	virtual std::shared_ptr<TreeNode> GenRootNode(const GameState& rootState) const = 0;
};

