#include "ColorHighlight.h"
#include <TextureRect.hpp>

using namespace godot;
void ColorHighlight::_register_methods()
{
}

void ColorHighlight::_init()
{
}

void ColorHighlight::_process(float delta)
{
}

void ColorHighlight::highlight(std::vector<Vector2> positions)
{
	int child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		TextureRect* highlight = cast_to<TextureRect>(get_child(i));
		highlight->set_global_position(positions[i]);
		highlight->set_visible(true);
	}
	set("time_remaining", 1.f);
}

void ColorHighlight::unhighlight()
{
	int child_count = get_child_count();
	for (int i = 0; i < child_count; ++i)
	{
		TextureRect* highlight = cast_to<TextureRect>(get_child(i));
		highlight->set_visible(false);
	}
}


