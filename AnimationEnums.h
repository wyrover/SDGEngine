#pragma once

namespace sidescroll
{
	enum EWrapMode
	{
		Once,
		Loop,
		Default,
		ClampForever
	};

	enum EPlayMode
	{
		StopSameLayer,
		StopAll
	};

	enum EQueueMode
	{
		CompleteOthers,
		PlayNow
	};
}
