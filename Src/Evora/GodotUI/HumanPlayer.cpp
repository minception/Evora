#include "HumanPlayer.h"
#include "GodotScenes.h"

void godot::HumanPlayer::move()
{
	ObjectLoader::tile_loader->interactive(true);
}
