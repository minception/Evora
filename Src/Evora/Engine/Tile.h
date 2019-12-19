#pragma once
namespace engine {
	class Tile
	{
	public:
		enum Type {
			empty = 0,
			red,
			yellow,
			blue,
			white,
			black
		};
		const Type GetType() { return m_type; }
	private:
		Type m_type;
	};
}
