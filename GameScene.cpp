#include "Precompiled.h"

namespace SDGEngine
{
	void GameScene::Init()
	{
		m_space = new Space;
		Start();
		m_space->Init();
	}

	void GameScene::Destroy()
	{
		Finish();
		if (m_space) m_space->Destroy();
		SDELETE(m_space);
	}

	void GameScene::Update(float delta)
	{
		m_space->Update(delta);
		OnUpdate(delta);
	}

	void GameScene::Render()
	{
		m_space->Render();
		OnRender();
	}

	void GameScene::ChangeScene(GameScene* state)
	{
		Singleton<SceneSystem>::GetSingleton()->ChangeScene(state);
	}
}
