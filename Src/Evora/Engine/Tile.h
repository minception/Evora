#pragma once
namespace engine {
	class Tile
	{
	public:
		enum class Type {
			empty = 0,
			red,
			yellow,
			blue,
			white,
			black
		};
		bool IsEmpty() { return m_type == Type::empty; }
		const Type GetType() { return m_type; }
	private:
		Type m_type;
	};
}
