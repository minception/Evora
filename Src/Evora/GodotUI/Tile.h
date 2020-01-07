#pragma once
#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <InputEvent.hpp>
#include <CollisionShape2D.hpp>
#include <Label.hpp>
#include <Input.hpp>


namespace godot
{
	class Tile:public Node2D
	{
		GODOT_CLASS(Tile, Node2D)
		int _enter_count = 0;
		bool _holding = false;
		Label* _label;
		Input* _input;
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);
		void _on_mouse_entered();
		void _area_input_event();
		Tile();
	};
}
