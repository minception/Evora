#include "MCTSAlgorithm.h"
#include <chrono>

void MCTSAlgorithm::DoIteration(const GameState& rootState, std::shared_ptr<TreeNode> rootNode)
{
	std::shared_ptr<TreeNode> node = rootNode;
	std::shared_ptr<GameState> state = rootState.Clone();

	// Select
	while (!node->HasMovesToTry() && node->HasChildren()) {
		node = node->SelectChild();
		state->DoMove(*node->GetMove());
	}

	// Expand
	if (node->HasMovesToTry()) {
		std::shared_ptr<const GameMove> move = node->SelectUntriedMove();
		state->DoMove(*move);
		node = node->AddChild(move, node, *state);
	}

	// Rollout
	while (!state->IsTerminal()) {
		state->DoMove(state->GetSimulationMove());
	}

	// Backpropagate
	while (node != nullptr) {
		node->Update(state->GetResult(node->GetPlayerWhoJustMoved()));
		node = node->GetParent();
	}
}

std::shared_ptr<const GameMove> MCTSAlgorithm::Search(const GameState& rootState, int time)
{
	auto start = std::chrono::system_clock::now();

	if (!mbSearch) {
		mbSearch = true;
	}

	mLastIterations = 0;

	std::shared_ptr<TreeNode> rootNode = mTreeCreator.GenRootNode(rootState);
	while (true)
	{
		++mLastIterations;
		auto iterationStart = std::chrono::system_clock::now();

		DoIteration(rootState, rootNode);

		auto now = std::chrono::system_clock::now();
		auto iterationTime = (std::chrono::duration<double>(now - iterationStart)).count();
		auto totalTime = (std::chrono::duration<double>(now - start)).count();
		if (iterationTime + totalTime > time)
		{
			break;
		}

		if (!mbSearch)
		{
			mbSearch = true;
			break;
		}
	}

#ifdef DEBUG
	rootNode->ChildrenToString(cout) << endl;
	//rootNode->TreeToString(cout, 0) << endl;
#endif // DEBUG

	return rootNode->GetBestMove();
}

const TreeNodeCreator& MCTSAlgorithm::GetTreeCreator() const
{
	return mTreeCreator;
}

int MCTSAlgorithm::GetLastIterations() const
{
	return mLastIterations;
}

void MCTSAlgorithm::Abort()
{
	mbSearch = false;
}

MCTSAlgorithm::~MCTSAlgorithm()
{
}
