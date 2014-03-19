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
		int z = 0;
		setActive(true);
		SetSpriteSort(true);

		// you don't have to delete this memory
		hero = new Entity(GetSpace(), "hero");
		hero->AddComponent<Sprite>();
		hero->SubscribeAllMessageType<Sprite>();

		hero->PostMessage<Sprite>(Message(MT_OBJECT_CREATED, "002-Fighter01.png"));
		hero->PostMessage<Sprite>(Message(MT_SET_TEXSCALE, D3DXVECTOR2(32.f, 48.f)));
		hero->PostMessage<Sprite>(Message(MT_SET_POSITION, D3DXVECTOR2(100.f, 100.f)));
		hero->PostMessage<Sprite>(Message(MT_SET_ZORDER, &z));

		hero2 = new Entity(GetSpace(), "hero2");
		hero2->AddComponent<Sprite>();
		hero2->SubscribeAllMessageType<Sprite>();

		hero2->PostMessage<Sprite>(Message(MT_OBJECT_CREATED, "002-Fighter01.png"));
		hero2->PostMessage<Sprite>(Message(MT_SET_TEXSCALE, D3DXVECTOR2(32.f, 48.f)));
		hero2->PostMessage<Sprite>(Message(MT_SET_POSITION, D3DXVECTOR2(80.f, 80.f)));
		z = 1;
		hero2->PostMessage<Sprite>(Message(MT_SET_ZORDER, &z));

		hero->SetActiveRecursively(true);
		hero2->SetActiveRecursively(true);

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

		if (Singleton<Input>::GetSingleton()->keyDown(DIK_Z))
		{
			Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_X))
		{
			Singleton<Engine>::GetSingleton()->Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_Q))
		{
			int zz = 1;
			hero->PostMessage<Sprite>(Message(MT_SET_ZORDER, &zz));
			zz = 0;
			hero2->PostMessage<Sprite>(Message(MT_SET_ZORDER, &zz));
		}
		if (Singleton<Input>::GetSingleton()->keyDown(DIK_W))
		{
			int zz = 0;
			hero->PostMessage<Sprite>(Message(MT_SET_ZORDER, &zz));
			zz = 1;
			hero2->PostMessage<Sprite>(Message(MT_SET_ZORDER, &zz));
		}
	}

	void LogoScene::OnRender()
	{
		m_Viewport->Render();
	}
}
