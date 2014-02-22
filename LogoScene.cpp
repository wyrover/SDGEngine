#include "Precompiled.h"

namespace sidescroll
{
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Start()
	{
		setActive(true);
		GameObject *hero = new GameObject(m_space, "hero");
		auto comp2 = hero->AddComponent<SpriteRenderer>();
	}

	void LogoScene::Finish()
	{

	}

	void LogoScene::OnUpdate(float delta)
	{
		if (INPUT->isButtonPress(MOUSE_RIGHT))
		{
			setFinished(true);
		}
	}

	void LogoScene::OnRender()
	{

	}
}
