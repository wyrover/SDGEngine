#pragma once

class GameScene : public Object
{
public:
	GameScene() {}
	virtual ~GameScene() {}

	bool isActive() { return m_active; }
	bool isFinished() { return m_finished; }
	void setActive(bool active) { m_active = active; }
	void setFinished(bool finish) { m_finished = finish; }

protected:
	Space *m_space;
	bool m_active = false;
	bool m_finished = false;
};
