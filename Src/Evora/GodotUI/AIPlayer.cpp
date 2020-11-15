#include "AIPlayer.h"
#include "ObjectLoader.h"

void godot::AIPlayer::move()
{
	ObjectLoader::tile_loader->interactive(false);
	if(m_worker.joinable())
	{
		m_worker.join();
	}
	m_worker = std::thread(&ai::ai::move, std::ref(*m_player));
}
