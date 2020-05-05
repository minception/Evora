#pragma once
#include "GameMove.h"
#include "command.h"

using namespace mcts;

class AzulGameMove : public GameMove
{
public:
	AzulGameMove(int move);
	virtual ~AzulGameMove();
	int GetMove() const;
	friend bool operator== (const AzulGameMove& lhs, const AzulGameMove& rhs);
	std::shared_ptr<control::command> generateCommand();
private:
	virtual ostream& ToString(ostream& ostr) const override;
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
