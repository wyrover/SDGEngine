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
			assets->RequestTexture(std::string(static_cast<const char *>(msg.m_data)));
			return MR_TRUE;
		case MT_UPDATE:
			return MR_TRUE;
		}

		return MR_IGNORED;
	}
}
