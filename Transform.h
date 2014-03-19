#pragma once

namespace SDGEngine
{
	struct Transform
	{
		D3DXVECTOR2 pos = D3DXVECTOR2(0.f, 0.f);
		float rot=0.f;
		D3DXVECTOR2 scale = D3DXVECTOR2(0.f, 0.f);
		int zorder = 0;
	};
}