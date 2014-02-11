#pragma once

class Component : public Object
{
	friend class GameObject;
public:
	Component() {}
	virtual ~Component() {}
	// disalbe copy and assign
	Component(const Component &rhs) = delete;
	void operator = (const Component &rhs) = delete;

	GameObject &gameObject() { return *m_gameObject; }
	virtual EMessageResult HandleMessage(const Message &) { return MR_IGNORED; }

private:
	GameObject *m_gameObject;
};