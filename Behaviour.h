#pragma once

class Behaviour : public Component
{
public:
	virtual ~Behaviour(){}
	bool enabled() { return m_enabled; }

private:
	bool m_enabled = false;
};
