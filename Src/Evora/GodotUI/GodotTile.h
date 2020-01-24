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
		
		bool _moving_back;
		Vector2 _speed;
		Vector2 _original_position;
		Input* _input;
		Ref<Texture> _texture;
		int _color;
		
		static Ref<Texture> blackTexture;
		static Ref<Texture> whiteTexture;
		static Ref<Texture> blueTexture;
		static Ref<Texture> redTexture;
		static Ref<Texture> yellowTexture;
		static Ref<Texture> starterTexture;
	public:
		bool _holding;
		int _factory_index;
		int _index;
		void set_color(int color);
		int get_color();
		static bool _holding_one;
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		void _on_mouse_entered();
		void _on_mouse_exited();
		void _area_input_event();
		bool pick_up(int factory, int color);
	};
}
