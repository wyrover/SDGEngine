#pragma once

class Behaviour : public Component
{
public:
	virtual ~Behaviour(){}
	bool enabled() { return m_enabled; }
	void setEnable(bool flag) { m_enabled = flag; }

private:
	bool m_enabled = false;
};
