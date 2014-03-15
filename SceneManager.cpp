#include "Precompiled.h"

namespace sidescroll
{
	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
		Destroy();
	}

	void SceneManager::Init()
	{
		Destroy();
	}

	void SceneManager::Destroy()
	{
		for (auto i : m_scene)
		{
			SDELETE(i);
		}
		m_scene.clear();
	}

	void SceneManager::Update(float delta)
	{
		// let the state update the game
		GameScene *scene = m_scene.back();
		if (scene && scene->isActive()) scene->Update(delta);
	}

	void SceneManager::Render()
	{
		// let the state update the game
		GameScene *scene = m_scene.back();
		if (scene && scene->isActive()) scene->Render();
	}

	void SceneManager::PushScene(GameScene* state)
	{
		// store and init the new state
		m_scene.push_back(state);
		m_scene.back()->Init();
	}

	void SceneManager::PopScene()
	{
		// cleanup the current state
		if (!m_scene.empty()) {
			m_scene.back()->Destroy();
			m_scene.pop_back();
		}
	}

	void SceneManager::ChangeScene(GameScene* state)
	{
		// cleanup the current state
		if (!m_scene.empty()) {
			m_scene.back()->Destroy();
			m_scene.pop_back();
		}

		// store and init the new state
		m_scene.push_back(state);
		m_scene.back()->Init();
	}
}
