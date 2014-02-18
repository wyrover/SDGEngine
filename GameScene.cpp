#include "Precompiled.h"

namespace sidescroll
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
		m_space->Destroy();
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

	void GameScene::setDeserialize(DeserializeFn fn)
	{
		m_deserialize = fn;
	}

	void GameScene::Deserialize(File &file)
	{
		if (m_deserialize)
		{
			m_deserialize(file);
		}
	}
}
