#include "Board.h"
#include "ObjectLoader.h"
#include "GodotTile.h"
#include "Root.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);
	register_class<Board>();
	register_class<BoardLoader>();
	register_class<FactoryLoader>();
	register_class<TileLoader>();
	register_class<GodotTile>();
	register_class<Root>();
}