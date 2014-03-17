#include "Precompiled.h"

namespace sidescroll
{
	FmodAudioSystem::~FmodAudioSystem()
	{
		ErrorHandle(m_system->close());
		ErrorHandle(m_system->release());
	}

	bool FmodAudioSystem::Init()
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&m_system);
		if (!ErrorHandle(result))
			return false;

		result = m_system->getVersion(&m_version);
		if (!ErrorHandle(result))
			return false;

		if (m_version < FMOD_VERSION)
		{
			printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", m_version, FMOD_VERSION);
			return false;
		}

		result = m_system->init(32, FMOD_INIT_NORMAL, 0);
		if (!ErrorHandle(result))
			return false;

		return true;
	}

	bool FmodAudioSystem::ErrorHandle(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return false;
		}

		return true;
	}
}