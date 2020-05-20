#pragma once
#include "GameState.h"
#include <random>
#include "game_controller.h"


class AzulGameState :
	public GameState
{
public:
	AzulGameState(std::shared_ptr<control::game_controller> state, int player);
	std::shared_ptr<GameState> Clone() const override;
	std::vector<std::shared_ptr<const GameMove>> GetMoves() const override;
	void DoMove(const GameMove& move) override;
	double GetResult(int player) const override;
	int GetWinner() const override;
	const GameMove& GetSimulationMove() const override;
	int GetPlayerWhoJustMoved() const override;
	bool IsTerminal() const override;
	std::shared_ptr<const GameMove> ParseMove(const std::string& move) const override;
private:
	int mPlayerWhoJustMoved;
	std::shared_ptr<control::game_controller> mState;
	int mWinner;
	bool mNotWin;
	std::vector<std::shared_ptr<const GameMove>> mMoves;
	std::vector<float> mMoveWeights;
	float mTotalWeight;
	void addMove(int factory_index, int pattern_line_index, int color, float weight);
	void CalculateMoves();
	std::shared_ptr<std::mt19937> randomEng;
};