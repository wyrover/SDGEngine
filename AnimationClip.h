#pragma once

namespace sidescroll
{
	class AnimationClip
	{
	public:
		AnimationClip() {}
		AnimationClip(const std::string &name, const D3DXVECTOR2 &start, const D3DXVECTOR2 &end, float speed, int idx);
		virtual ~AnimationClip();

		void Save(XMLFileNode *file);
		void Load(XMLFileNode *file);

		bool m_isPlaying;
		std::string m_name;
		D3DXVECTOR2 offset;
		D3DXVECTOR2 scale;
		float time;
		int index;
	};
}
