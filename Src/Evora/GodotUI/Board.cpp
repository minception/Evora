#include "Board.h"
#include "Utils.h"

using namespace godot;

void Board::_register_methods() {
	register_method("_process", &Board::_process);
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
