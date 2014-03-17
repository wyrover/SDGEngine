#include "Precompiled.h"

namespace SDGEngine
{
	Bounds::Bounds(D3DXVECTOR2 center, D3DXVECTOR2 size)
		: m_center(center), m_size(size), m_extents(size / 2)
	{
		// setting min, max vector
		m_min.x = m_center.x - m_extents.x;
		m_min.y = m_center.y - m_extents.y;
		m_max.x = m_center.x + m_extents.x;
		m_max.y = m_center.y + m_extents.y;
	}

	Bounds::Bounds(const Bounds &bounds)
	{
		m_min = bounds.m_min;
		m_max = bounds.m_max;
		m_center = bounds.m_center;
		m_extents = bounds.m_extents;
		m_size = bounds.m_size;
	}

	Bounds &Bounds::operator = (const Bounds &bounds)
	{
		m_min = bounds.m_min;
		m_max = bounds.m_max;
		m_center = bounds.m_center;
		m_extents = bounds.m_extents;
		m_size = bounds.m_size;

		return (*this);
	}

	bool Bounds::Contains(D3DXVECTOR2 point)
	{
		// the point is not intersect with rectangle
		if (point.x < m_min.x || point.x > m_max.x) return false;
		if (point.y < m_min.y || point.y > m_max.y) return false;

		// intersection found
		return true;
	}

	void Bounds::Expand(float amount)
	{
		D3DXVECTOR2 size(m_size);
		size.x += amount;
		size.y += amount;
		Bounds bounds(m_center, size);
		(*this) = bounds;
	}

	void Bounds::Expand(D3DXVECTOR2 amount)
	{
		Bounds bounds(m_center, m_size + amount);
		(*this) = bounds;
	}

	bool Bounds::Intersects(Bounds &bounds)
	{
		// Exit with no intersection if found separated along an axis
		if (bounds.m_max.x < m_min.x || bounds.m_min.x > m_max.x) return false;
		if (bounds.m_max.y < m_min.y || bounds.m_min.y > m_max.y) return false;

		// No separating axis found, therefor there is at least one overlapping axis
		return true;
	}

	void Bounds::setMinMax(D3DXVECTOR2 min, D3DXVECTOR2 max)
	{
		m_min = min;
		m_max = max;
	}

	float Bounds::sqrDistance(D3DXVECTOR2 point)
	{
		return sqrt((point.x - m_center.x)*(point.x - m_center.x) + (point.y - m_center.y)*(point.y - m_center.y));
	}

}
