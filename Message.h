#pragma once

namespace sidescroll
{
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
