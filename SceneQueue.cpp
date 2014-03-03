#include "Precompiled.h"

namespace sidescroll
{
	GameScene *SceneQueue::m_current = nullptr;
	void SceneQueue::Init()
	{

	}

	void SceneQueue::Destroy()
	{
		m_current = nullptr;
		removeAll();
	}

	void SceneQueue::Update(float delta)
	{
		if (m_SceneQueue.empty())
			return;

		GameScene *q = m_SceneQueue.front();
		if (m_current != q)
		{
			m_current = q;
			m_current->Init();
		}
		else
		{
			if (m_current && !m_current->isFinished() && m_current->isActive())
			{
				m_current->Update(delta);
			}
		}
	}

	void SceneQueue::Render()
	{
		if (m_SceneQueue.empty())
			return;

		GameScene *q = m_SceneQueue.front();
		if (m_current != q)
		{
			m_current = q;
			m_current->Init();
		}
		else
		{
			if (m_current && !m_current->isFinished() && m_current->isActive())
			{
				m_current->Render();
			}
			else if (m_current->isFinished())
			{
				remove();
			}
		}
	}

	void SceneQueue::add(GameScene *scene)
	{
		m_SceneQueue.push(scene);
	}

	void SceneQueue::remove()
	{
		if (m_SceneQueue.empty())
			return;
		m_SceneQueue.front()->Destroy();
		m_SceneQueue.pop();
	}

	void SceneQueue::removeAll()
	{
		unsigned i = getSize();
		for (unsigned j = 0; j < i; j++) {
			m_SceneQueue.front()->Destroy();
			SDELETE(m_SceneQueue.front());
			m_SceneQueue.pop();
		}
	}

	size_t SceneQueue::getSize()
	{ 
		return m_SceneQueue.size(); 
	}

	bool SceneQueue::isEmpty()
	{
		return m_SceneQueue.empty();
	}
}
