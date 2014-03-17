#include "Precompiled.h"

namespace SDGEngine
{
	AnimationClip::AnimationClip(const std::string &name, const D3DXVECTOR2 &start, const D3DXVECTOR2 &end, float speed, int idx)
		: m_name(name), offset(start), scale(end), time(speed), index(idx), m_isPlaying(false)
	{}

	AnimationClip::~AnimationClip()
	{}

	void AnimationClip::Save(XMLFileNode *file)
	{
		file->Write("name", m_name);

		file->Write("offset", offset);
		file->Write("scale", scale);
		file->Write("time", time);
		file->Write("index", index);
	}

	void AnimationClip::Load(XMLFileNode *file)
	{
		file->Read("name", m_name);

		file->Read("offset", offset);
		file->Read("scale", scale);
		file->Read("time", time);
		file->Read("index", index);
	}
}