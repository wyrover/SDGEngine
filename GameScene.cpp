#include "Precompiled.h"

GameScene *GSM = nullptr;

void GameScene::Init()
{
	GSM = this;
	L = ENGINE->LuaState();
	Lua::CallFunc(L, "RegisterStates", "script/");
	m_next = "Test1";

	REGISTER_FUNC_TO_LUA(L, SetNextState);
}

void GameScene::Destroy()
{
	GSM = nullptr;
}

void GameScene::Update(float delta)
{
	if (m_current == m_next)
	{
		const char *state = m_current.c_str();
		Lua::CallFunc(L, "CallStateFunction", state, "Update", delta);
	}
	else
	{
		if (m_current.size())
			Lua::CallFunc(L, "CallStateFunction", m_current.c_str(), "Finish");

		if (m_next == "Restart")
			m_next = m_current;
		else
		{
			m_current = m_next;
			assert(!m_current.empty());
		}

		const char *state = m_current.c_str();
		Lua::CallFunc(L, "CallStateFunction", state, "Start");
		Lua::CallFunc(L, "CallStateFunction", state, "Update", delta);
	}
}

void GameScene::Render()
{

}

void GameScene::SetNextState(const char *state)
{
	GSM->m_next = state;
}