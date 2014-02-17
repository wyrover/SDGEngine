#include "Precompiled.h"

LogoScene::LogoScene()
{
}

LogoScene::~LogoScene()
{
}

void LogoScene::Init()
{
	m_space = new Space;
	m_space->Init();

	setActive(true);
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
	m_space->Destroy();
	SDELETE(m_space);
}

void LogoScene::Update(float delta)
{
	m_space->Update(delta);
}

void LogoScene::Render()
{
	m_space->Render();
}