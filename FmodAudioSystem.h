#pragma once

namespace sidescroll
{
	class FmodAudioSystem : public Singleton<FmodAudioSystem>
	{
	public:
		FmodAudioSystem() {}
		virtual ~FmodAudioSystem();

		bool Init();
		FMOD::System *AudioSystem() { return m_system; }
		bool ErrorHandle(FMOD_RESULT result);

	private:
		FMOD::System *m_system = nullptr;
		unsigned int m_version;
		DISALLOW_COPY_AND_ASSIGN(FmodAudioSystem);
	};
}