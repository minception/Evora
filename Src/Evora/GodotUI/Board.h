#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <OptionButton.hpp>

#include "AIFactory.h"
#include "Utils.h"

namespace godot {
	class Board : public Node2D {
		GODOT_CLASS(Board, Node2D)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _ready();

		Board();
	};

	inline void Board::_ready()
	{
		OptionButton* player_select = (OptionButton*)get_child(get_child_index(this, "Player"));
		player_select->add_item("Human", 0);
		auto ai_factories = AI::AIFactory::get_factories();
		int64_t player_index = 1;
		for (auto&& ai_factory : ai_factories)
		{
			player_select->add_item(ai_factory.first, player_index++);
		}
		
	}
}
