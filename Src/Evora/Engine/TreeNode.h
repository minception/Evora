#pragma once

#include "GameMove.h"
#include "GameState.h"
#include <memory>

class TreeNode
{
public:
	virtual ~TreeNode() = 0;
	virtual std::shared_ptr<TreeNode> AddChild(std::shared_ptr<const GameMove> move, std::shared_ptr<TreeNode> parent, const GameState& state) = 0;
	virtual std::shared_ptr<const GameMove> GetBestMove() const = 0;
	virtual bool HasChildren() const = 0;
	virtual bool HasMovesToTry() const = 0;
	virtual std::shared_ptr<const GameMove> GetMove() const = 0;
	virtual std::shared_ptr<TreeNode> GetParent() const = 0;
	virtual int GetPlayerWhoJustMoved() const = 0;
	virtual std::shared_ptr<TreeNode> SelectChild() const = 0;
	virtual std::shared_ptr<const GameMove> SelectUntriedMove() const = 0;
	virtual void Update(double result) = 0;
};

