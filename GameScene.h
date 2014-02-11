#pragma once

class GameScene;
extern GameScene *GSM;
class GameScene : public Object
{
public:
	GameScene() {}
	~GameScene() {}

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update(float delta) override;
	virtual void Render() override;

	static void SetNextState(const char *state);

private:
	std::string m_current;
	std::string m_next;
	lua_State *L;
};
