#pragma once
#include "GameState.h"
#include <random>
#include "game_controller.h"

using namespace mcts;

class AzulGameState :
	public GameState
{
public:
	AzulGameState(control::game_controller state, int player);
	shared_ptr<GameState> Clone() const override;
	vector<shared_ptr<const GameMove>> GetMoves() const override;
	void DoMove(const GameMove& move) override;
	double GetResult(int player) const override;
	int GetWinner() const override;
	const GameMove& GetSimulationMove() const override;
	int GetPlayerWhoJustMoved() const override;
	bool IsTerminal() const override;
	shared_ptr<const GameMove> ParseMove(const string& move) const override;
private:
	ostream& ToString(ostream& ostr) const override;
	// const static int directions[4][2];
	int mPlayerWhoJustMoved;
	control::game_controller mState;
	int mWinner;
	bool mNotWin;
	vector<shared_ptr<const GameMove>> mMoves;
	void addMove(int factory_index, int pattern_line_index, int color);
	void CalculateMoves();
	bool CheckWinDirections(int player, int x, int y);
	int Near(int player, int x, int y, int dx, int dy);
	shared_ptr<mt19937> randomEng;
};