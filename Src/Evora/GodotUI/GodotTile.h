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
		int _factory_index;
		int _pattern_line_index;
		int _board_index;
		
		bool m_clicked;
		Vector2 m_clicked_on;
		Vector2 m_original_position;
		bool m_selected;
		bool _interactive;
		bool m_follow_mouse;
		bool m_move_back;
		
		bool m_animating;
		Vector2 m_animating_to;

		static Ref<Texture> blackTexture;
		static Ref<Texture> whiteTexture;
		static Ref<Texture> blueTexture;
		static Ref<Texture> redTexture;
		static Ref<Texture> yellowTexture;
		static Ref<Texture> starterTexture;
	public:
		
		void set_color(int color);
		int get_color();

		void set_interactive(bool cond);
		bool get_interactive();

		void set_pattern_line_index(int value);
		int get_pattern_line_index();
		void set_text(String text);

		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		void _on_mouse_entered();
		void _on_mouse_exited();
		void _area_input_event();
		void set_select(bool cond);
		void set_highlight(bool cond);
		void set_follow(bool cond);
		void set_move_back(bool cond);
		void animate_to(Vector2 position);
	};
}
