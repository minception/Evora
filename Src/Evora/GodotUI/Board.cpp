#include "Board.h"
#include "Utils.h"

using namespace godot;

void Board::_register_methods() {
	register_method("_process", &Board::_process);
	register_method("_ready", &Board::_ready);
}

void godot::Board::_init()
{
}

void godot::Board::_process(float delta)
{
}

godot::Board::Board()
{
}
