#pragma once
#include "GameMove.h"
#include "command.h"


class AzulGameMove : public GameMove
{
public:
	AzulGameMove(int move);
	virtual ~AzulGameMove();
	int GetMove() const override;
	friend bool operator== (const AzulGameMove& lhs, const AzulGameMove& rhs);
	std::unique_ptr<control::command> generateCommand(int player_index) const;
private:
	int mMove;
	int mFactoryId;
	int mPatternLine;
	int mColor;
};

namespace std
{
	template<> struct hash<AzulGameMove>
	{
		typedef AzulGameMove argument_type;
		typedef size_t result_type;
		result_type operator()(const argument_type& f) const
		{
			return std::hash<int>()(f.GetMove());
		}
	};
};
