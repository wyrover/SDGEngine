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
		SetSpriteSort(true);

		//m_Tilemap = new TileMap("tileset.png", 32, 32, 32, 25);
		//Singleton<Viewport>::GetSingleton()->Init(m_Tilemap, 20, 20);

		//// you don't have to delete this memory
		//hero = new Entity(GetSpace(), "hero");
		//hero->AddComponent<Sprite>();
		//hero->SubscribeAllMessageType<Sprite>();

		//hero->PostMessage<Sprite>(Message(MT_LOAD_TEXTURE, "002-Fighter01.png"));
		//hero->PostMessage<Sprite>(Message(MT_SET_TEXSCALE, D3DXVECTOR2(32.f, 48.f)));
		//hero->PostMessage<Sprite>(Message(MT_SET_POSITION, D3DXVECTOR2(100.f, 100.f)));

		//hero->SetActiveRecursively(true);

		ttf = new TTF("content/DroidSansMono.ttf", 11);
	}

	void LogoScene::Finish()
	{
		SDELETE(ttf);
		//SDELETE(m_Tilemap);
	}

	void LogoScene::OnUpdate(float delta)
	{

	}

	void LogoScene::OnRender()
	{
		ttf->RenderText(100, 100, "hello");
	}
}
