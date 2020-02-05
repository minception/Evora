#include "game_controller.h"
#include "init_round.h"

using namespace control;

void game_controller::start_game()
{
	m_commands.emplace_back(std::make_unique<init_round>(m_model));
	step();
}

void game_controller::add_command(std::unique_ptr<command> command)
{
	m_commands.push_back(std::move(command));
}

bool game_controller::step()
{
	if(current_command == m_commands.size())
	{
		return false;
	}
	m_commands[current_command]->Execute();
	current_command++;
	return true;
}
