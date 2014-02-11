#pragma once

class Collider : public Component
{
public:
	Collider();
	virtual ~Collider();

	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float delta) override;
	virtual void Render() override;

private:
	struct AABB
	{
		D3DXVECTOR2 min, max;
	};

	bool AABBvsAABB(AABB& a, AABB& b);
	D3DXVECTOR2 Clamp(AABB& a, AABB& b);
	bool collide;
};
