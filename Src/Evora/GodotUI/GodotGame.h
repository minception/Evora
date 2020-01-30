#pragma once
#include "game.h"
#include <Node2D.hpp>
#include <vector>

#include "ObjectLoader.h"
#include "Factory.h"

namespace godot
{
	class ObjectLoader;
	using namespace model;
	class GodotGame : public game
	{
		bool wait_for_refill;
	public:
		GodotGame(int players) :game(players) {}
		int bag_to_factories() override;
	};
}
