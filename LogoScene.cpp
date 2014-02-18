#include "Precompiled.h"

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
	auto comp1 = hero->AddComponent<TextComponent>();
	auto comp2 = hero->AddComponent<Renderer>();
	comp1->setText("this is hero");

	hero->SubscribeToMessageType<TextComponent>(MT_OBJECT_CREATED);
	hero->SubscribeToMessageType<Renderer>(MT_OBJECT_CREATED);

	Message msg(MT_OBJECT_CREATED);
	hero->BroadcastMessage(msg);
	//hero->SetActiveRecursively(true);
}

void LogoScene::Finish()
{

}

void LogoScene::OnUpdate(float delta)
{
	if (ENGINE->INPUT()->keyPress(DIK_A))
	{
		setFinished(true);
	}
}

void LogoScene::OnRender()
{
	std::cout << "LogoScene OnRender()" << std::endl;
}
