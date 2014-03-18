#include "Precompiled.h"

namespace SDGEngine
{
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
		Destroy();
	}

	void LogoScene::Start()
	{
		setActive(true);

		// you don't have delete this memory
		//GameObject *hero = new GameObject(m_space, "hero");
		//hero->AddComponent<Sprite>();
		//hero->SubscribeToMessageType<Sprite>(MT_OBJECT_CREATED);
		//Message msg(MT_OBJECT_CREATED, "002-Fighter01.png");
		//hero->PostMessage<Sprite>(msg);
		//hero->SetActiveRecursively(true);

		m_Tilemap = new TileMap("tileset.png", 32, 32, 32, 25);
		m_Viewport = new Viewport(m_Tilemap, 20, 20);
	}

	void LogoScene::Finish()
	{
		SDELETE(m_Tilemap);
		SDELETE(m_Viewport);
	}

	void LogoScene::OnUpdate(float delta)
	{
		m_Viewport->Update();
	}

	void LogoScene::OnRender()
	{
		m_Viewport->Render();
	}
}
