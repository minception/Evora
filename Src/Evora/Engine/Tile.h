#pragma once
#include <memory>
namespace engine {
	enum class type {
		empty = 0,
		starter,
		red,
		yellow,
		blue,
		white,
		black
	};
	
	class tile
	{
	public:
		bool is_empty() const { return m_type == type::empty; }
		type get_type() const { return m_type; }
		void set_type(const type type) { m_type = type; }
	private:
		type m_type;
	public:
		explicit tile(type type);
	};
}
