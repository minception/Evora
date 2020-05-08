#pragma once

#include "TreeNode.h"
#include <random>

class UCTTreeNode : public TreeNode
{
public:
	UCTTreeNode(std::shared_ptr<const GameMove> move, std::shared_ptr<UCTTreeNode> parent, const GameState& state, double constant = 1.0, bool generateUntriedMoves = true);
	virtual ~UCTTreeNode() = default;
	UCTTreeNode(const UCTTreeNode& src);
	UCTTreeNode& operator=(const UCTTreeNode& rhs);
	UCTTreeNode(UCTTreeNode&& src) noexcept;
	UCTTreeNode& operator=(UCTTreeNode&& rhs) noexcept;

	std::shared_ptr<TreeNode> AddChild(std::shared_ptr<const GameMove> move, std::shared_ptr<TreeNode> parent, const GameState& state) override;
	std::shared_ptr<const GameMove> GetBestMove() const override;
	bool HasChildren() const override;
	bool HasMovesToTry() const override;
	std::shared_ptr<const GameMove> GetMove() const override;
	std::shared_ptr<TreeNode> GetParent() const override;
	int GetPlayerWhoJustMoved() const override;
	std::shared_ptr<TreeNode> SelectChild() const override;
	std::shared_ptr<const GameMove> SelectUntriedMove() const override;
	void Update(double result) override;

protected:
	std::vector<std::shared_ptr<UCTTreeNode>> mChildNodes;
	std::vector<std::shared_ptr<const GameMove>> mUntriedMoves;
	int mVisits;
	double mConstant;
private:
	void CopyFrom(const UCTTreeNode& src);
	void FreeMemory();
	void MoveFrom(const UCTTreeNode& src);
	double UCTValue() const;

	std::weak_ptr<UCTTreeNode> mParent;
	std::shared_ptr<const GameMove> mMove;
	double mWins;
	int mPlayerWhoJustMoved;
	std::shared_ptr<std::mt19937> randomEng;
};