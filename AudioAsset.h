#pragma once

namespace SDGEngine
{
	class AudioAsset : public Asset
	{
	public:
		AudioAsset();
		virtual ~AudioAsset();

		bool Load(const std::string &filename, FMOD_MODE mode);
		virtual void Reload() override;
		virtual void Unload() override;
		void Play();
		bool isPlaying();
		void Pause(bool pause);
		FMOD::Sound *getSound();
		void setVolume(float volume);
		float getVolume();

	private:
		FMOD::Sound *m_sound;
		FMOD::Channel *m_channel = 0;
		FMOD_MODE m_mode;
	};
}
