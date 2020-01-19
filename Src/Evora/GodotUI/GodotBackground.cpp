#include "GodotBackground.h"
#include <SceneTree.hpp>
#include <Viewport.hpp>

using namespace godot;

void godot::GodotBackground::_register_methods()
{
	register_method("_on_window_resize", &GodotBackground::_on_window_resize);
	register_signal<GodotBackground>("_on_window_resize", Dictionary());
}

void GodotBackground::_init()
{
}

void GodotBackground::_ready()
{
	get_tree()->get_root()->connect("size_changed", this, "_on_window_resize");
}

void GodotBackground::_on_window_resize()
{
	set_size(get_viewport_rect().size);
}
