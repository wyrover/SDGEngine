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

		m_TileTempalte = new TileMap("tileset.png", 32, 32, 10, 10);
		m_TileEngine = new Viewport(m_TileTempalte, 32 * 5, 32 * 5);
	}

	void LogoScene::Finish()
	{
		SDELETE(m_TileTempalte);
		SDELETE(m_TileEngine);
	}

	void LogoScene::OnUpdate(float delta)
	{
		m_TileEngine->Update();
		//if (MySingleton<Input>::GetSingleton()->isButtonPress(MOUSE_RIGHT))
		//{
		//	ChangeScene(new TitleScene);
		//}
	}

	void LogoScene::OnRender()
	{
		m_TileEngine->Render();
	}
}
