#pragma once

class GameScene : public Object
{
public:
	GameScene() {}
	virtual ~GameScene() {}

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update(float delta) override;
	virtual void Render() override;

	bool isActive() { return m_active; }
	bool isFinished() { return m_finished; }

protected:
	Space *m_space;
	bool m_active = false;
	bool m_finished = false;
};
