#pragma once

namespace sidescroll
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
