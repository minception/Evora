#include "Board.h"
#include "Factory.h"
#include "GameData.h"
#include "GodotTile.h"
#include "ObjectLoader.h"
#include "PatternLine.h"
#include "Root.h"
#include "PatternLineLoader.h"
#include "Floor.h"
#include "Center.h"
#include "ColorHighlight.h"

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
	register_class<Factory>();
	register_class<BoardLoader>();
	register_class<FactoryLoader>();
	register_class<TileLoader>();
	register_class<GodotTile>();
	register_class<Root>();
	register_class<PatternLine>();
	register_class<PatternLineLoader>();
	register_class<GameData>();
	register_class<Floor>();
	register_class<Center>();
	register_class<ColorHighlight>();
}