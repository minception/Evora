#include "AIPlayer.h"
#include "ObjectLoader.h"

void godot::AIPlayer::move()
{
	ObjectLoader::tile_loader->interactive(false);
	m_player->move();
}
