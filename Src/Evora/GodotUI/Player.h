﻿#pragma once
#include "game_controller.h"

namespace godot
{
	class Player
	{
	public:
		virtual void move() = 0;
	};
}