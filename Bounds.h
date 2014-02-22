#pragma once

namespace sidescroll
{
	struct BoundsVerts
	{
		float x, y, z, rhw = 1.0f;
		DWORD color;
		static const DWORD BoundsFvF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	};

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

	private:
		D3DXVECTOR2 m_min, m_max;
		D3DXVECTOR2 m_center;
		D3DXVECTOR2 m_extents;
		D3DXVECTOR2 m_size;
		BoundsVerts m_verts;
	};
}
