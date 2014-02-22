#include "Precompiled.h"

namespace sidescroll
{
	void SceneQueue::Init()
	{

	}

	void SceneQueue::Destroy()
	{
		deleteAllFromRemovedQueue();
	}

	void SceneQueue::Update(float delta)
	{
		if (m_SceneQueue.empty())
			return;

		GameScene *scene = m_SceneQueue.front();
		if (scene && !scene->isFinished() && scene->isActive())
		{
			scene->Update(delta);
		}
	}

	void SceneQueue::Render()
	{
		if (m_SceneQueue.empty())
			return;

		GameScene *scene = m_SceneQueue.front();
		if (scene && !scene->isFinished() && scene->isActive())
		{
			scene->Render();
		}
		else if (scene->isFinished())
		{
			removeFromSceneQueue();
		}
	}

	void SceneQueue::addFromSceneQueue(GameScene *scene)
	{
		scene->Init();
		m_SceneQueue.push(scene);
	}

	void SceneQueue::removeFromSceneQueue()
	{
		if (m_SceneQueue.empty())
			return;
		m_SceneQueue.front()->Destroy();
		m_RemovedSceneQueue.push(m_SceneQueue.front());
		m_SceneQueue.pop();
	}

	void SceneQueue::removeAllFromSceneQueue()
	{
		unsigned i = getSceneQueueSize();
		for (unsigned j = 0; j < i; j++) {
			m_SceneQueue.front()->Destroy();
			m_RemovedSceneQueue.push(m_SceneQueue.front());
			m_SceneQueue.pop();
		}
	}

	void SceneQueue::deleteAllFromRemovedQueue()
	{
		removeAllFromSceneQueue();
		unsigned i = m_RemovedSceneQueue.size();
		for (unsigned j = 0; j < i; j++) {
			SDELETE(m_RemovedSceneQueue.front());
			m_RemovedSceneQueue.pop();
		}
	}

	size_t SceneQueue::getSceneQueueSize()
	{ 
		return m_SceneQueue.size(); 
	}

	bool SceneQueue::isEmpty()
	{
		return m_SceneQueue.empty();
	}
}
