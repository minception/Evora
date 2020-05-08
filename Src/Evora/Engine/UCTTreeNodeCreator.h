#pragma once
#include "TreeNodeCreator.h"

class UCTTreeNodeCreator :public TreeNodeCreator
{
public:
	UCTTreeNodeCreator(float constant = 1.0f): mConstant(constant){}
	virtual ~UCTTreeNodeCreator() = default;
	std::shared_ptr<TreeNode> GenRootNode(const GameState& rootState) const override;
private:
	float mConstant;
};