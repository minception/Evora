#pragma once

#include "TreeNodeCreator.h"

class MCTSAlgorithm
{
public:
	MCTSAlgorithm(const TreeNodeCreator& treeCreator):mTreeCreator(treeCreator), mbSearch(true), mLastIterations(0){}
	virtual ~MCTSAlgorithm();
	MCTSAlgorithm& operator=(const MCTSAlgorithm& rhs) = delete;
	MCTSAlgorithm(MCTSAlgorithm&& rhs) noexcept = delete;
	MCTSAlgorithm& operator=(MCTSAlgorithm&& rhs) noexcept = delete;

	std::shared_ptr<const GameMove> Search(const GameState& rootState, int time);
	void Abort();
	const TreeNodeCreator& GetTreeCreator() const;
	int GetLastIterations() const;
private:
	const TreeNodeCreator& mTreeCreator;
	bool mbSearch;
	int mLastIterations;
	static void DoIteration(const GameState& rootState, std::shared_ptr<TreeNode> rootNode);
};
