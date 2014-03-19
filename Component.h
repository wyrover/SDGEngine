#pragma once

namespace SDGEngine
{
	class Entity;
	class Component : public Object
	{
	public:
		Component() {}
		virtual ~Component() {}

		Entity *gameObject() { return m_gameObject; }
		virtual EMessageResult HandleMessage(const Message &) { return MR_IGNORED; }

	private:
		Entity *m_gameObject;
		DISALLOW_COPY_AND_ASSIGN(Component);
		friend class Entity;
	};
}
