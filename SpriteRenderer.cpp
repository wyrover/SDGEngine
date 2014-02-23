#include "Precompiled.h"

namespace sidescroll
{
	SpriteRenderer::SpriteRenderer()
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Init()
	{
		//TextureAtlas textureAtlas;
		//TiXmlElement element("script/test.xml");
		//textureAtlas.Load(&element);
	}

	void SpriteRenderer::Destroy()
	{

	}

	void SpriteRenderer::Update(float delta)
	{
		
	}

	void SpriteRenderer::Render()
	{
		
	}

	EMessageResult SpriteRenderer::HandleMessage(const Message &msg)
	{
		switch (msg.m_type)
		{
		case MT_OBJECT_CREATED:
			return MR_TRUE;
		case MT_UPDATE:
			return MR_TRUE;
		}

		return MR_IGNORED;
	}
}
