#pragma once

class AABBTreeCollider : public Collider
{
public:
	AABBTreeCollider();
	virtual ~AABBTreeCollider();

	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float delta) override;
	virtual void Render() override;

private:
	bool Collide(const AABBCollisionNode& a, const AABBCollisionNode& b) const;
	bool BoxBoxOverlap(float ex0, float cen0, float ex1, float cen1);
	D3DXVECTOR2 Clamp(const AABBCollisionNode& a, const AABBCollisionNode& b) const;
};
