#pragma once
#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <Label.hpp>
#include <Input.hpp>
#include <core/Ref.hpp>
#include <Texture.hpp>
#include <TextureRect.hpp>
#include "tile.h"


namespace godot
{
	class GodotTile:public Node2D
	{
		GODOT_CLASS(GodotTile, Node2D)
		
		Label* _label;
		TextureRect* _image;
		TextureRect* _highlight;
		
		bool _holding;
		bool _moving_back;
		Vector2 _speed;
		Vector2 _original_position;
		Input* _input;
		Ref<Texture> _texture;
		model::tile _color;
	public:
		static bool _holding_one;
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		void _on_mouse_entered();
		void _on_mouse_exited();
		void _area_input_event();
		model::tile get_color() const;
		void set_color(model::tile color);
	};
}
