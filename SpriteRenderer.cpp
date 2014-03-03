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
		SDELETE(m_sprites);
	}

	void SpriteRenderer::Update(float delta)
	{

	}

	void SpriteRenderer::Render()
	{
		if (m_sprites && m_isVisible)
		{
			m_sprites->Render();
		}
	}

	EMessageResult SpriteRenderer::HandleMessage(const Message &msg)
	{
		switch (msg.m_type)
		{
		case MT_OBJECT_CREATED:
			m_sprites = new Sprite(std::string(static_cast<char *>(msg.m_data)));
			return MR_TRUE;
		case MT_UPDATE:
			return MR_TRUE;
		}

		return MR_IGNORED;
	}
}
