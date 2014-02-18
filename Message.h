#pragma once

namespace sidescroll
{
	class Message
	{
	public:
		Message() {}
		Message(EMessageType type) :m_type(type) {}
		Message(EMessageType type, void *data) : m_type(type), m_data(data) {}

	public:
		EMessageType m_type;
		void *m_data;
	};
}
