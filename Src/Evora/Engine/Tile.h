#pragma once
namespace engine {
	enum class type {
		empty = 0,
		red,
		yellow,
		blue,
		white,
		black
	};
	class tile
	{
	public:
		bool IsEmpty() { return m_type == type::empty; }
		const type GetType() { return m_type; }
	private:
		type m_type;
	public:
		tile(type type);
	};
}
