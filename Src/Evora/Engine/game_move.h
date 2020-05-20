#pragma once


class game_move
{
public:
	virtual ~game_move();
	virtual int get_move() const = 0;
};

