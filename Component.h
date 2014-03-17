#pragma once

namespace SDGEngine
{
	class Component : public Object
	{
	public:
		Component() {}
		virtual ~Component() {}

		GameObject &gameObject() { return *m_gameObject; }
		virtual EMessageResult HandleMessage(const Message &) { return MR_IGNORED; }

	private:
		GameObject *m_gameObject;
		DISALLOW_COPY_AND_ASSIGN(Component);
		friend class GameObject;
	};
}
