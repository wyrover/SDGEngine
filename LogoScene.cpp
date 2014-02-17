#include "Precompiled.h"

LogoScene::LogoScene()
{
}

LogoScene::~LogoScene()
{
}

void LogoScene::Init()
{
	GameScene::Init();
	m_active = true;
	GameObject *hero = new GameObject(m_space, "hero");
	auto comp1 = hero->AddComponent<TextComponent>();
	auto comp2 = hero->AddComponent<Renderer>();
	comp1->setText("hello component based object management!");

	hero->SubscribeToMessageType<TextComponent>(MT_OBJECT_CREATED);
	hero->SubscribeToMessageType<Renderer>(MT_OBJECT_CREATED);

	Message msg(MT_OBJECT_CREATED);
	hero->BroadcastMessage(msg);
	//hero->SetActiveRecursively(true);
}

void LogoScene::Destroy()
{
	GameScene::Destroy();
}

void LogoScene::Update(float delta)
{
	GameScene::Update(delta);
}

void LogoScene::Render()
{
	GameScene::Render();
}