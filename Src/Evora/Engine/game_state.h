#pragma once
#include "game_move.h";
#include <vector>
#include <string>
#include <memory>
#include <random>

class game_state
{
public:
	virtual ~game_state();
	virtual std::shared_ptr<game_state> clone() const = 0;
	virtual std::shared_ptr<std::mt19937> get_rng() const = 0;
	virtual std::vector<std::shared_ptr<const game_move>> get_moves() const = 0;
	virtual void do_move(const game_move& move) = 0;
	virtual double get_result(int player) const = 0;
	virtual int get_winner() const = 0;
	virtual const game_move& get_simulation_move(bool heavy_playouts) const = 0;
	virtual int get_player_who_just_moved() const = 0;
	virtual bool is_terminal() const = 0;
	virtual std::shared_ptr<const game_move> parse_move(const std::string& move) const = 0;
};

