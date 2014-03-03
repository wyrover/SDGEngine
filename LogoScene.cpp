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

		//TextureAtlas textureAtlas;
		//TiXmlDocument xmlDoc;
		//if (xmlDoc.LoadFile(ASSETS->GetContentPath() + "atlas.xml") == false)
		//	std::cout << "LoadFile failed!" << std::endl;
		//TiXmlElement *xmlTextureAtlas = xmlDoc.FirstChildElement("TextureAtlas");
		//if (xmlTextureAtlas)
		//{
		//	textureAtlas.Load(xmlTextureAtlas);
		//}

		//GameObject *hero = new GameObject(m_space, "logo");
		//hero->AddComponent<SpriteRenderer>();
		//hero->SubscribeToMessageType<SpriteRenderer>(MT_OBJECT_CREATED);
		//Message msg(MT_OBJECT_CREATED, "logo.png");
		//hero->PostMessage<SpriteRenderer>(msg);
		//hero->SetActiveRecursively(true);
	}

	void LogoScene::Finish()
	{

	}

	void LogoScene::OnUpdate(float delta)
	{
		if (INPUT->isButtonPress(MOUSE_RIGHT))
		{
			setFinished(true);
		}
	}

	void LogoScene::OnRender()
	{

	}
}
