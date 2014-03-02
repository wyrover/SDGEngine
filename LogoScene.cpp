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
		hero->AddComponent<SpriteRenderer>();
		hero->SubscribeToMessageType<SpriteRenderer>(MT_OBJECT_CREATED);
		Message msg(MT_OBJECT_CREATED, "texture/desk.jpg");
		hero->PostMessage<SpriteRenderer>(msg);
		hero->SetActiveRecursively(true);
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
