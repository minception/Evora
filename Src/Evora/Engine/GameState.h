#pragma once
#include "GameMove.h";
#include <vector>
#include <string>
#include <memory>

class GameState
{
public:
	virtual ~GameState();
	virtual std::shared_ptr<GameState> Clone() const = 0;
	virtual std::vector<std::shared_ptr<const GameMove>> GetMoves() const = 0;
	virtual void DoMove(const GameMove& move) = 0;
	virtual double GetResult(int player) const = 0;
	virtual int GetWinner() const = 0;
	virtual const GameMove& GetSimulationMove() const = 0;
	virtual int GetPlayerWhoJustMoved() const = 0;
	virtual bool IsTerminal() const = 0;
	virtual std::shared_ptr<const GameMove> ParseMove(const std::string& move) const = 0;
};

