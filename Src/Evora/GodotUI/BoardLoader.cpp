#include "BoardLoader.h"
#include "Root.h"
#include "ObjectLoader.h"
#include <TextureRect.hpp>
#include "Utils.h"
#include "GodotScenes.h"

void godot::BoardLoader::_register_methods()
{
	register_method("_ready", &BoardLoader::_ready);
}

void godot::BoardLoader::_ready()
{
	ObjectLoader::board_loader = this;
}

void godot::BoardLoader::_init()
{
	m_board_scene = GodotScenes::board_scene;
}

void godot::BoardLoader::_process(float delta)
{
}

void godot::BoardLoader::load_boards(int count, Vector2 viewport_size)
{
	for (int i = 0; i < count; ++i)
	{
		Node2D* board = (Node2D*)m_board_scene->instance();
		String image_name("Image");
		TextureRect* board_picture = (TextureRect*)board->get_child(get_child_index(board, image_name));
		real_t posx = (viewport_size.x - 10.f - board_picture->get_size().x) / (count - 1) * i + 5.f;
		real_t posy = viewport_size.y - 10.f - board_picture->get_size().y;
		board->set_global_position(Vector2(posx, posy));
		add_child(board);
	}
}
