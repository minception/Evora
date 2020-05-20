#pragma once
#include "game_move.h"
#include "command.h"


class azul_game_move : public game_move
{
public:
	azul_game_move(int move);
	virtual ~azul_game_move();
	int get_move() const override;
	friend bool operator== (const azul_game_move& lhs, const azul_game_move& rhs);
	std::unique_ptr<control::command> generate_command(int player_index) const;
private:
	int m_move;
	int m_factory_id;
	int m_pattern_line;
	int m_color;
};

namespace std
{
	template<> struct hash<azul_game_move>
	{
		typedef azul_game_move argument_type;
		typedef size_t result_type;
		result_type operator()(const argument_type& f) const
		{
			return std::hash<int>()(f.get_move());
		}
	};
};
