#include "FactoryLoader.h"
#include "Node2D.hpp"
#include "Root.h"
#include <cmath>
#include "ResourceLoader.hpp"
#include "TextureRect.hpp"
#include "Utils.h"
#include "ObjectLoader.h"
#include "GodotScenes.h"

using namespace godot;

void FactoryLoader::_register_methods()
{
	register_method("_ready", &FactoryLoader::_ready);
}

void FactoryLoader::_ready()
{
	ObjectLoader::factory_loader = this;
}

void FactoryLoader::_init()
{
}

void FactoryLoader::load_factories(int count, Vector2 c, float r)
{
	for (int i = 0; i < count; ++i)
	{
		Factory* factory = (Factory*)GodotScenes::factory_scene->instance();
		TextureRect* image = (TextureRect*)factory->get_node("Image");
		Vector2 size = image->get_size();
		float angle = Math_PI/2.f + 2.f*Math_PI*i/count;
		float posx = c.x - std::cos(angle) * r - size.x/2.f;
		float posy = c.y - std::sin(angle) * r - size.y/2.f;
		factory->set_global_position(Vector2(posx, posy));
		add_child(factory);
	}
}
