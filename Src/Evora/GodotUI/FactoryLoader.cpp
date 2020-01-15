#include "FactoryLoader.h"

void godot::FactoryLoader::_register_methods()
{
	register_method("_ready", &FactoryLoader::_ready);
}

void godot::FactoryLoader::_ready()
{
	Root::p_factory_loader = this;
}

void godot::FactoryLoader::_init()
{
}

void godot::FactoryLoader::_process(float delta)
{
}

godot::FactoryLoader::FactoryLoader()
{
	ResourceLoader* rl = ResourceLoader::get_singleton();
	m_factory_scene = rl->load("res://Factory.tscn");
}
