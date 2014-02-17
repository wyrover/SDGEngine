#pragma once

class Collider : public Component
{
public:
	Collider() {}
	virtual ~Collider() {}

private:
	bool collide = false;
};
