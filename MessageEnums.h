#pragma once

namespace SDGEngine
{
	enum EMessageType
	{
		MT_OBJECT_CREATED,
		MT_SET_TEXSCALE,
		MT_SET_TEXOFFSET,
		MT_SET_POSITION,
		MT_SET_ROTATION,
		MT_SET_SCALE,
		MT_SET_ZORDER,
		NUM_MESSAGE_TYPES
	};

	enum EMessageResult
	{
		MR_FALSE,
		MR_TRUE,
		MR_IGNORED,
		MR_ERROR
	};
}
