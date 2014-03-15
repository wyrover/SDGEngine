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

		// you don't have delete this memory
		//GameObject *hero = new GameObject(m_space, "hero");
		//hero->AddComponent<Sprite>();
		//hero->SubscribeToMessageType<Sprite>(MT_OBJECT_CREATED);
		//Message msg(MT_OBJECT_CREATED, "002-Fighter01.png");
		//hero->PostMessage<Sprite>(msg);
		//hero->SetActiveRecursively(true);

		Fighter = new Sprite("002-Fighter01.png");
		back = new TileSet("tileset.png", 32.f, 32.f, 2);
		//AudioAsset *res = MySingleton<Assets>::GetSingleton()->RequestAudio("battle_with_red1.mp3");
		//res->Play();
	}

	void LogoScene::Finish()
	{
		SDELETE(Fighter);
	}

	void LogoScene::OnUpdate(float delta)
	{
		if (MySingleton<Input>::GetSingleton()->isButtonPress(MOUSE_RIGHT))
		{
			ChangeScene(new TitleScene);
		}
		if (MySingleton<Input>::GetSingleton()->keyDown(DIK_A))
			Fighter->setOffPosition(-300.f*delta, 0);
		else if (MySingleton<Input>::GetSingleton()->keyDown(DIK_D))
			Fighter->setOffPosition(300.f*delta, 0);
		else if (MySingleton<Input>::GetSingleton()->keyDown(DIK_W))
			Fighter->setOffPosition(0, -300.f*delta);
		else if (MySingleton<Input>::GetSingleton()->keyDown(DIK_S))
			Fighter->setOffPosition(0, 300.f*delta);
	}

	void LogoScene::OnRender()
	{
		back->Render();
		Fighter->Render();
	}
}
