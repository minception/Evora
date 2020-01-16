#include "FactoryLoader.h"
#include "Node2D.hpp"
#include "Root.h"
#include <cmath>
#include "ResourceLoader.hpp"
#include "TextureRect.hpp"
#include "Utils.h"

using namespace godot;

void FactoryLoader::_register_methods()
{
	register_method("_ready", &FactoryLoader::_ready);
}

void FactoryLoader::_ready()
{
	Root::p_factory_loader = this;
}

void FactoryLoader::_init()
{
}

void FactoryLoader::_process(float delta)
{
}

void FactoryLoader::load_factories(int count, Vector2 c, float r)
{
	for (int i = 0; i < count; ++i)
	{
		Node2D* factory = (Node2D*)m_factory_scene->instance();
		String image_name("Image");
		TextureRect* image = (TextureRect*)factory->get_child(get_child_index(factory, image_name));
		Vector2 size = image->get_size();
		float angle = Math_PI/2 + 2*Math_PI*i/count;
		float posx = c.x - std::cos(angle) * r - size.x/2;
		float posy = c.y - std::sin(angle) * r - size.y/2;
		printf("%f, %f\n", posx, posy);
		factory->set_global_position(Vector2(posx, posy));
		add_child(factory);
	}
}

FactoryLoader::FactoryLoader()
{
	ResourceLoader* rl = ResourceLoader::get_singleton();
	m_factory_scene = rl->load("res://Factory.tscn");
}
