#include "Precompiled.h"

namespace sidescroll
{
	AudioAsset::AudioAsset()
		:Asset(ASSET_AUDIO)
	{
		
	}

	AudioAsset::~AudioAsset()
	{
		Unload();
	}

	bool AudioAsset::Load(const std::string &filename, FMOD_MODE mode)
	{
		m_filename = filename;
		m_mode = mode;
		FMOD_RESULT result;
		result = MySingleton<AudioManager>::GetSingleton()->AudioSystem()->createSound(filename.c_str(), FMOD_HARDWARE, 0, &m_sound);
		if (!MySingleton<AudioManager>::GetSingleton()->ErrorHandle(result))
			return false;
		
		result = m_sound->setMode(mode);
		if (!MySingleton<AudioManager>::GetSingleton()->ErrorHandle(result))
			return false;

		return true;
	}

	void AudioAsset::Reload()
	{
		Unload();
		Load(m_filename, m_mode);
	}
	
	void AudioAsset::Unload()
	{
		FMOD_RESULT result;
		result = m_sound->release();
		if (!MySingleton<AudioManager>::GetSingleton()->ErrorHandle(result))
			return;
	}

	void AudioAsset::Play()
	{
		MySingleton<AudioManager>::GetSingleton()->AudioSystem()->playSound(FMOD_CHANNEL_FREE, m_sound, false, &m_channel);
	}

	bool AudioAsset::isPlaying()
	{
		bool playing;
		m_channel->isPlaying(&playing);
		return playing;
	}

	void AudioAsset::Pause(bool pause)
	{
		bool paused = pause;
		m_channel->setPaused(paused);
	}

	FMOD::Sound *AudioAsset::getSound()
	{
		FMOD::Sound *currentsound = 0;
		m_channel->getCurrentSound(&currentsound);
		return currentsound;
	}

	void AudioAsset::setVolume(float volume)
	{
		m_channel->setVolume(volume);
	}

	float AudioAsset::getVolume()
	{
		float volume;
		m_channel->getVolume(&volume);
		return volume;
	}
}