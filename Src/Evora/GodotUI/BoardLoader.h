﻿#pragma once
#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Resource.hpp>
#include <ResourceLoader.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include "Root.h"
#include <Texture.hpp>

namespace godot
{
	class BoardLoader :public Node2D
	{
		GODOT_CLASS(BoardLoader, Node2D)
		Ref<PackedScene> m_board_scene;
	public:
		static void _register_methods();
		void _ready();
		void _init();
		void _process(float delta);
		void load_boards(int count, Vector2 viewport_size);
	};
}
