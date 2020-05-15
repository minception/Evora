#pragma once


class GameMove
{
public:
	virtual ~GameMove();
	virtual int GetMove() const = 0;
};

