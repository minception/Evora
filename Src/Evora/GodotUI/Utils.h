#pragma once
#include <Node.hpp>

namespace godot
{
	static int get_child_index(Node* node, const String& name)
	{
		int64_t cchildren = node->get_child_count();
		for (int i = 0; i < cchildren; ++i)
		{
			if (node->get_child(i)->get_name() == name) return i;
		}
		return -1;
	}

	
}