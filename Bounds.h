#pragma once

namespace sidescroll
{
	class Bounds
	{
	public:
		explicit Bounds() {}
		explicit Bounds(D3DXVECTOR2 center, D3DXVECTOR2 size);
		Bounds(const Bounds &bounds);

		Bounds &operator = (const Bounds &bounds);

		bool Contains(D3DXVECTOR2 point);
		void Expand(float amount);
		void Expand(D3DXVECTOR2 amount);
		bool Intersects(Bounds &bounds);
		void setMinMax(D3DXVECTOR2 min, D3DXVECTOR2 max);
		float sqrDistance(D3DXVECTOR2 point); // retrn to point to box center distance

		const D3DXVECTOR2 getMin() const { return m_min; }
		const D3DXVECTOR2 getMax() const { return m_max; }
		D3DXVECTOR2 &getMin() { return m_min; }
		D3DXVECTOR2 &getMax() { return m_max; }

	private:
		D3DXVECTOR2 m_min, m_max;
		D3DXVECTOR2 m_center;
		D3DXVECTOR2 m_extents;
		D3DXVECTOR2 m_size;
		//BoundsVerts m_verts;
	};
}
