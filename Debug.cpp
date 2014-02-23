#include "Precompiled.h"

namespace sidescroll
{
	Debug *LOGGER = nullptr;
	Debug::Debug()
	{
		LOGGER = this;
	}

	Debug::~Debug()
	{
		LOGGER = nullptr;
	}
}