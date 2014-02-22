#pragma once

namespace sidescroll
{
	class Sprite
	{
	public:
		Sprite() {}
		~Sprite() {}

	private:
		Bounds m_bounds;
		RECT m_rect;
	};
}
