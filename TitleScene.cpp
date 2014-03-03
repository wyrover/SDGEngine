#include "Precompiled.h"

namespace sidescroll
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Start()
	{
		setActive(true);
		GameObject *hero = new GameObject(m_space, "title");
		hero->AddComponent<SpriteRenderer>();
		hero->SubscribeToMessageType<SpriteRenderer>(MT_OBJECT_CREATED);
		Message msg(MT_OBJECT_CREATED, "desk.jpg");
		hero->PostMessage<SpriteRenderer>(msg);
		hero->SetActiveRecursively(true);
	}

	void TitleScene::Finish()
	{

	}

	void TitleScene::OnUpdate(float delta)
	{
		
	}

	void TitleScene::OnRender()
	{

	}
}
