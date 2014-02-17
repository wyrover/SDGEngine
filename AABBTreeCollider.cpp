#include "Precompiled.h"

AABBTreeCollider::AABBTreeCollider()
{
	//auto iter = m_shapes.begin();
	//for (iter; iter != m_shapes.end(); ++iter)
	//{
	//	auto oter = m_shapes.begin();
	//	for (oter; oter != m_shapes.end(); ++oter)
	//	{
	//		if (*iter != *oter)
	//		{
	//			AABBShape *a = dynamic_cast<AABBShape *>(*iter);
	//			AABBShape *b = dynamic_cast<AABBShape *>(*oter);
	//			if( a != NULL && b != NULL)
	//			{
	//				if( AABBvsAABB(a->aabb, b->aabb) )
	//				{
	//					collide = true;
	//					Vec2 tmp = Clamp(a->aabb, b->aabb);
	//					if( tmp.x != 0)
	//					{
	//						if( tmp.x < 0 )
	//						{
	//							// 오른쪽
	//							a->aabb.min.x += tmp.x - 1.f;
	//							a->aabb.max.x += tmp.x - 1.f;
	//						}
	//						else
	//						{
	//							// 왼쪽
	//							a->aabb.min.x += tmp.x + 1.f;
	//							a->aabb.max.x += tmp.x + 1.f;
	//						}
	//					}
	//					else if( tmp.y != 0)
	//					{
	//						if( tmp.y > 0 )
	//						{
	//							// 아래쪽
	//							a->aabb.min.y += tmp.y + 1.f;
	//							a->aabb.max.y += tmp.y + 1.f;
	//						}
	//						else
	//						{
	//							// 위쪽
	//							a->aabb.min.y += tmp.y - 1.f;
	//							a->aabb.max.y += tmp.y - 1.f;
	//						}
	//					}
	//				}
	//				else
	//				{
	//					collide = false;
	//				}
	//			}
	//		}
	//	}
	//}
}

AABBTreeCollider::~AABBTreeCollider()
{
}

void AABBTreeCollider::Init()
{

}

void AABBTreeCollider::Destroy()
{

}

void AABBTreeCollider::Update(float delta)
{

}

void AABBTreeCollider::Render()
{
	std::cout << "Renderer Render" << std::endl;
}

bool AABBTreeCollider::Collide(const AABBCollisionNode& a, const AABBCollisionNode& b) const
{
	// Exit with no intersection if found separated along an axis
	if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

	// No separating axis found, therefor there is at least one overlapping axis
	return true;
}

bool AABBTreeCollider::BoxBoxOverlap(float ex0, float cen0, float ex1, float cen1)
{
	return false;
}

D3DXVECTOR2 AABBTreeCollider::Clamp(const AABBCollisionNode& a, const AABBCollisionNode& b) const
{
	static D3DXVECTOR2 mtd(0.f, 0.f);

	float left = (b.min.x - a.max.x);
	float right = (b.max.x - a.min.x);
	float top = (b.min.y - a.max.y);
	float bottom = (b.max.y - a.min.y);

	if (left > 0 || right < 0) return mtd;
	if (top > 0 || bottom < 0) return mtd;

	if (fabs(left) < right)
		mtd.x = left;
	else
		mtd.x = right;

	if (fabs(top) < bottom)
		mtd.y = top;
	else
		mtd.y = bottom;

	// 0 the axis with the largest mtd value.
	if (fabs(mtd.x) < fabs(mtd.y))
		mtd.y = 0;
	else
		mtd.x = 0;

	return mtd;
}
