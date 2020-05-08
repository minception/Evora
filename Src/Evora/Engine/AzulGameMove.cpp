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
	mPatternLine = (mMove << 4) & mask;
	mColor = (mMove << 8) & mask;
}

AzulGameMove::~AzulGameMove()
{
}

int AzulGameMove::GetMove() const
{
	return mMove;
}

std::shared_ptr<control::command> AzulGameMove::generateCommand()
{
	if(mFactoryId < 7)
	{

		if (mPatternLine < model::COLORS)
		{
			return std::make_shared<control::factory_offer>(mFactoryId, 0, mPatternLine, (model::tile)mColor);
		}
		return std::make_shared<control::drop_factory>(mFactoryId, 0, (model::tile)mColor);
	}
	if(mPatternLine < model::COLORS)
	{
		return std::make_shared<control::center_offer>(0, mPatternLine, (model::tile)mColor);
	}
	return std::make_shared<control::drop_center>(0, (model::tile)mColor);
}

bool operator==(const AzulGameMove& lhs, const AzulGameMove& rhs)
{
	return lhs.mMove == rhs.mMove;
}
