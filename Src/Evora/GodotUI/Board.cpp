#include "Board.h"

using namespace godot;

void Board::_register_methods() {
	register_method((char*)"_process", &Board::_process);

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

godot::Board::~Board()
{
}
