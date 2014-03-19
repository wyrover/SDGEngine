#include "Precompiled.h"

namespace SDGEngine
{
	SceneSystem::SceneSystem()
	{
	}

	SceneSystem::~SceneSystem()
	{
		Destroy();
	}

	void SceneSystem::Init()
	{
		Destroy();
	}

	void SceneSystem::Destroy()
	{
		for (auto i : m_scene)
		{
			SDELETE(i);
		}
		m_scene.clear();
	}

	void SceneSystem::Update(float delta)
	{
		// let the state update the game
		Scene *scene = m_scene.back();
		if (scene && scene->isActive()) scene->Update(delta);
	}

	void SceneSystem::Render()
	{
		// let the state update the game
		Scene *scene = m_scene.back();
		if (scene && scene->isActive()) scene->Render();
	}

	void SceneSystem::PushScene(Scene* state)
	{
		// store and init the new state
		m_scene.push_back(state);
		m_scene.back()->Init();
	}

	void SceneSystem::PopScene()
	{
		// cleanup the current state
		if (!m_scene.empty()) {
			m_scene.back()->Destroy();
			m_scene.pop_back();
		}
	}

	void SceneSystem::ChangeScene(Scene* state)
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
