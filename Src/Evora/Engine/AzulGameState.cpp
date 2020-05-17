#include "AzulGameState.h"
#include "AzulGameMove.h"

#include "game.h"
#include <memory>
#include <memory>
#include <memory>
#include <memory>

AzulGameState::AzulGameState(std::shared_ptr<control::game_controller> state, int player) :
	mPlayerWhoJustMoved(player),
	mWinner(0),
	mNotWin(true),
	mState(state)
{
	CalculateMoves();
	std::random_device rndDevice;
	randomEng = std::make_shared<std::mt19937>(rndDevice());
}

std::shared_ptr<GameState> AzulGameState::Clone() const
{
	auto cloned = std::make_shared<AzulGameState>(*this);
	cloned->mState = std::make_shared<control::game_controller>(*mState);
	return cloned;
}

std::vector<std::shared_ptr<const GameMove>> AzulGameState::GetMoves() const
{
	return mMoves;
}

void AzulGameState::DoMove(const GameMove& move)
{
	const AzulGameMove& azulMove = dynamic_cast<const AzulGameMove&>(move);
	std::unique_ptr<control::command> command = azulMove.generateCommand(mPlayerWhoJustMoved);
	mState->add_command(std::move(command));
 	while (mState->step())
	{
	}
	mMoves.clear();
	mPlayerWhoJustMoved = mState->get_current_player();
	CalculateMoves();
	int movessize = mMoves.size();
	if(IsTerminal())
	{
		mWinner = mState->get_winner();
		mNotWin = false;
	}
}

double AzulGameState::GetResult(int player) const
{
	if (mWinner == player)
	{
		return 1.0;
	}
	return 0.0;
}

int AzulGameState::GetWinner() const
{
	return mWinner;
}

const GameMove& AzulGameState::GetSimulationMove() const
{
	std::uniform_int_distribution<int> dist(0, mMoves.size() - 1);
	return *mMoves[dist(*randomEng)];
}

int AzulGameState::GetPlayerWhoJustMoved() const
{
	return mPlayerWhoJustMoved;
}

bool AzulGameState::IsTerminal() const
{
	return mState->game_over();
}

std::shared_ptr<const GameMove> AzulGameState::ParseMove(const std::string& move) const
{
	return std::dynamic_pointer_cast<const GameMove>(std::make_shared<const AzulGameMove>(stoi(move)));
}

void AzulGameState::addMove(int factory_index, int pattern_line_index, int color)
{
	int move = factory_index | (pattern_line_index << 4) | (color << 8);
	mMoves.push_back(std::make_shared<AzulGameMove>(move));
}

void AzulGameState::CalculateMoves()
{
	if (mNotWin)
	{
		for (int factory_index = 0; factory_index <= mState->get_model()->factory_count(); ++factory_index)
		{
			std::vector<model::tile> colors;
			if(factory_index == mState->get_model()->factory_count())
			{
				colors = mState->get_model()->get_center_colors();
			}
			else
			{
				colors = mState->get_model()->get_factory_colors(factory_index);
			}
			for (auto&& color : colors)
			{
				for(int pattern_line_index = 0; pattern_line_index < model::COLORS; ++pattern_line_index)
				{
					if(mState->get_model()->can_add_to_pattern_line(mPlayerWhoJustMoved, pattern_line_index, color))
					{
						addMove(factory_index, pattern_line_index, (int)color);
					}
				}
				// for every color adding move to floor
				addMove(factory_index, model::COLORS, (int)color);
			}
		}
	}
}
