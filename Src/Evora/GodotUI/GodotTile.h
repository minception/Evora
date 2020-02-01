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
		Input* _input;
		
		int _color;

		bool m_clicked;
		Vector2 m_clicked_on;
		bool m_selected;
		bool _interactive;
		bool m_follow_mouse;

		static Ref<Texture> blackTexture;
		static Ref<Texture> whiteTexture;
		static Ref<Texture> blueTexture;
		static Ref<Texture> redTexture;
		static Ref<Texture> yellowTexture;
		static Ref<Texture> starterTexture;
	public:
		int _factory_index;
		
		void set_color(int color);
		int get_color();

		void set_interactive(bool cond);
		bool get_interactive();
		
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		void _on_mouse_entered();
		void _on_mouse_exited();
		void _area_input_event();
		void set_select(int factory, int color, bool cond);
		void set_highlight(int factory, int color, bool cond);
		void set_follow(int factory, int color, bool cond);
	};
}
