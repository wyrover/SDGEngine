#pragma once

namespace SDGEngine
{
	enum EMessageType
	{
		MT_OBJECT_CREATED,
		MT_LOAD_TEXTURE,
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

	class Message
	{
	public:
		Message() {}
		explicit Message(EMessageType type) :m_type(type) {}
		Message(EMessageType type, void *data) : m_type(type), m_data(data) {}
		Message(const Message &rhs) { m_type = rhs.m_type; m_data = rhs.m_data; }
		Message &operator =(const Message &rhs) { m_type = rhs.m_type; m_data = rhs.m_data; }

	public:
		EMessageType m_type;
		void *m_data;
	};
}
