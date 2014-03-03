#include "Precompiled.h"

namespace sidescroll
{
	AudioAsset::AudioAsset()
		:Asset(ASSET_AUDIO)
	{
	}

	AudioAsset::~AudioAsset()
	{
	}

	bool AudioAsset::Load(const std::string &filename)
	{
		return true;
	}

	void AudioAsset::Reload()
	{
		Unload();
		Load(m_filename);
	}
	
	void AudioAsset::Unload()
	{

	}
}