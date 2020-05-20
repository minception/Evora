#include "AzulGameMove.h"
#include <iostream>
#include "center_offer.h"
#include "drop_center.h"
#include "factory_offer.h"
#include "drop_factory.h"
#include <memory>

AzulGameMove::AzulGameMove(int move) :
	mMove(move)
{
	int mask = 0b1111;
	mFactoryId = mMove & mask;
	mPatternLine = (mMove >> 4) & mask;
	mColor = (mMove >> 8) & mask;
}

AzulGameMove::~AzulGameMove()
{
}

int AzulGameMove::GetMove() const
{
	return mMove;
}

std::unique_ptr<control::command> AzulGameMove::generateCommand(int player_index) const
{
	if (mFactoryId < 5)
	{

		if (mPatternLine < model::COLORS)
		{
			return std::make_unique<control::factory_offer>(mFactoryId, player_index, mPatternLine, (model::tile)mColor);
		}
		return std::make_unique<control::drop_factory>(mFactoryId, player_index, (model::tile)mColor);
	}
	if (mPatternLine < model::COLORS)
	{
		return std::make_unique<control::center_offer>(player_index, mPatternLine, (model::tile)mColor);
	}
	return std::make_unique<control::drop_center>(player_index, (model::tile)mColor);
}

bool operator==(const AzulGameMove& lhs, const AzulGameMove& rhs)
{
	return lhs.mMove == rhs.mMove;
}
