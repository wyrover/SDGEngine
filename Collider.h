#pragma once

namespace SDGEngine
{
	class Collider : public Component
	{
	public:
		Collider() {}
		virtual ~Collider() {}

	private:
		bool collide = false;
	};
}
