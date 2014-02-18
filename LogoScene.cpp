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
		auto comp2 = hero->AddComponent<Renderer>();
		hero->SubscribeToMessageType<Renderer>(MT_OBJECT_CREATED);

		Message msg(MT_OBJECT_CREATED);
		char * texname = "texture/desk.jpg";
		msg.m_data = static_cast<void *>(texname);
		hero->PostMessage<Renderer>(msg);
		hero->SetActiveRecursively(true);
	}

	void LogoScene::Finish()
	{

	}

	void LogoScene::OnUpdate(float delta)
	{
		if (ENGINE->INPUT()->isButtonPress(MOUSE_RIGHT))
		{
			setFinished(true);
		}
	}

	void LogoScene::OnRender()
	{

	}
}
