#include "BoardLoader.h"
#include "Root.h"

void godot::BoardLoader::_register_methods()
{
	register_method("_ready", &BoardLoader::_ready);
}

void godot::BoardLoader::_ready()
{
	Root::p_board_loader = this;
}

void godot::BoardLoader::_init()
{
	
}

void godot::BoardLoader::_process(float delta)
{
}

godot::BoardLoader::BoardLoader()
{
	ResourceLoader* rl = ResourceLoader::get_singleton();
	m_board_scene = rl->load("res://Board.tscn");
}
