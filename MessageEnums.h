#pragma once

namespace sidescroll
{
	enum EMessageType
	{
		MT_UPDATE,
		MT_OBJECT_CREATED,
		NUM_MESSAGE_TPYES
	};

	enum EMessageResult
	{
		MR_FALSE,
		MR_TRUE,
		MR_IGNORED,
		MR_ERROR
	};
}
