#pragma once
#include <string>

class game_move
{
public:
	virtual ~game_move();
	virtual int get_move() const = 0;
	virtual float get_value() const = 0;
	virtual std::string to_string() const = 0;
};

