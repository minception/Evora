#include "UCTTreeNode.h"
#include <memory>

UCTTreeNode::UCTTreeNode(std::shared_ptr<const GameMove> move, std::shared_ptr<UCTTreeNode> parent,
                         const GameState& state, double constant, bool generateUntriedMoves)
	:mMove(move), mParent(parent), mConstant(constant), mWins(0), mVisits(0)
{
	mPlayerWhoJustMoved = state.GetPlayerWhoJustMoved();
	if(generateUntriedMoves)
	{
		mUntriedMoves = state.GetMoves();
	}
	std::random_device rng;
	randomEng = std::make_shared<std::mt19937>(rng());
}

UCTTreeNode::UCTTreeNode(const UCTTreeNode& src)
{
	CopyFrom(src);
}

UCTTreeNode& UCTTreeNode::operator=(const UCTTreeNode& rhs)
{
	// Check for self-assignment
	if (this != &rhs)
	{
		FreeMemory();
		CopyFrom(rhs);
	}
	return *this;
}

UCTTreeNode::UCTTreeNode(UCTTreeNode&& src) noexcept
{
	MoveFrom(src);
}

UCTTreeNode& UCTTreeNode::operator=(UCTTreeNode&& rhs) noexcept
{
	if (this!= &rhs)
	{
		MoveFrom(rhs);
	}
	return *this;
}

std::shared_ptr<TreeNode> UCTTreeNode::AddChild(std::shared_ptr<const GameMove> move, std::shared_ptr<TreeNode> parent, const GameState& state)
{
	std::shared_ptr<UCTTreeNode> n = std::make_shared<UCTTreeNode>(move, std::dynamic_pointer_cast<UCTTreeNode>(parent), state, mConstant);
	mUntriedMoves.erase(remove(mUntriedMoves.begin(), mUntriedMoves.end(), move), mUntriedMoves.end());
	mChildNodes.push_back(n);
	return n;
}

std::shared_ptr<const GameMove> UCTTreeNode::GetBestMove() const
{
	std::vector<std::shared_ptr<UCTTreeNode>> sortedChildNodes(mChildNodes);
	std::sort(sortedChildNodes.begin(), sortedChildNodes.end(), [](std::shared_ptr<UCTTreeNode> x, std::shared_ptr<UCTTreeNode> y) {return x->mVisits > y->mVisits; });
	return sortedChildNodes[0]->mMove;
}

bool UCTTreeNode::HasChildren() const
{
	return !mChildNodes.empty();
}

bool UCTTreeNode::HasMovesToTry() const
{
	return !mUntriedMoves.empty();
}

int UCTTreeNode::GetPlayerWhoJustMoved() const
{
	return mPlayerWhoJustMoved;
}

std::shared_ptr<TreeNode> UCTTreeNode::GetParent() const
{
	return mParent.lock();
}

std::shared_ptr<const GameMove> UCTTreeNode::GetMove() const
{
	return mMove;
}

std::shared_ptr<TreeNode> UCTTreeNode::SelectChild() const
{
	std::vector<std::shared_ptr<UCTTreeNode>> sortedChildNodes(mChildNodes);
	sort(sortedChildNodes.begin(), sortedChildNodes.end(), [](std::shared_ptr<UCTTreeNode> x, std::shared_ptr<UCTTreeNode> y) {return x->UCTValue() < y->UCTValue(); });
	return sortedChildNodes[0];
}

std::shared_ptr<const GameMove> UCTTreeNode::SelectUntriedMove() const
{
	std::uniform_int_distribution<int> dist(0, mUntriedMoves.size() - 1);
	return mUntriedMoves[dist(*randomEng)];
}

void UCTTreeNode::CopyFrom(const UCTTreeNode& src)
{
	for(auto& child: src.mChildNodes)
	{
		mChildNodes.push_back(std::make_shared <UCTTreeNode> (*child));
	}
	mUntriedMoves = src.mUntriedMoves;
	mVisits = src.mVisits;
	mConstant = src.mConstant;
	mMove = src.mMove;
	mWins = src.mWins;
	mPlayerWhoJustMoved = src.mPlayerWhoJustMoved;
	randomEng = src.randomEng;
}

void UCTTreeNode::FreeMemory()
{
	mChildNodes.clear();
	mParent.reset();
}

void UCTTreeNode::MoveFrom(const UCTTreeNode& src)
{
	mChildNodes = std::move(mChildNodes);
	mUntriedMoves = std::move(src.mUntriedMoves);
	mVisits = std::move(src.mVisits);
	mConstant = std::move(src.mConstant);
	mMove = std::move(src.mMove);
	mWins = std::move(src.mWins);
	mPlayerWhoJustMoved = std::move(src.mPlayerWhoJustMoved);
	randomEng = std::move(src.randomEng);
}

void UCTTreeNode::Update(double result)
{
	++mVisits;
	mWins += result;
}

double UCTTreeNode::UCTValue() const
{
	auto parent = mParent.lock();
	return mWins / mVisits + mConstant * sqrt(2 * log(parent->mVisits) / mVisits);
}


