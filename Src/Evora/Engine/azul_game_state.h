#pragma once
#include "game_state.h"
#include "game_controller.h"


class azul_game_state :
	public game_state
{
public:
	azul_game_state(std::shared_ptr<control::game_controller> state, int player);
	std::shared_ptr<game_state> clone() const override;
	std::vector<std::shared_ptr<const game_move>> get_moves() const override;
	void do_move(const game_move& move) override;
	double get_result(int player) const override;
	int get_winner() const override;
	const game_move& get_simulation_move() const override;
	int get_player_who_just_moved() const override;
	bool is_terminal() const override;
	std::shared_ptr<const game_move> parse_move(const std::string& move) const override;
private:
	int m_current_player;
	std::shared_ptr<control::game_controller> m_state;
	int m_winner;
	bool m_not_win;
	std::vector<std::shared_ptr<const game_move>> m_moves;
	std::vector<float> m_move_weights;
	float m_total_weight;
	void add_move(int factory_index, int pattern_line_index, int color, float weight);
	void calculate_moves();
	std::shared_ptr<std::mt19937> m_rng;

	virtual std::shared_ptr<std::mt19937> get_rng() const override;
};