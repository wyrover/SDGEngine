#include "Precompiled.h"

namespace SDGEngine
{
	void Scene::Init()
	{
		m_space = new Space;
		Start();
		m_space->Init();
	}

	void Scene::Destroy()
	{
		Finish();
		if (m_space) m_space->Destroy();
		SDELETE(m_space);
	}

	void Scene::Update(float delta)
	{
		m_space->Update(delta);
		OnUpdate(delta);
	}

	void Scene::Render()
	{
		OnRender();
		m_space->Render();
	}

	void Scene::ChangeScene(Scene* state)
	{
		Singleton<SceneSystem>::GetSingleton()->ChangeScene(state);
	}
}
