#include "Precompiled.h"

namespace sidescroll
{
	SpriteRenderer::SpriteRenderer()
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
		SDELETE(m_sprites);
	}

	void SpriteRenderer::Init()
	{

	}

	void SpriteRenderer::Destroy()
	{

	}

	void SpriteRenderer::Update(float delta)
	{
		if (INPUT->keyDown(DIK_RIGHT))
			m_sprites->setOffPosition(300 * delta, 0);
		else if (INPUT->keyDown(DIK_LEFT))
			m_sprites->setOffPosition(-300 * delta, 0);
		else if (INPUT->keyDown(DIK_UP))
			m_sprites->setOffPosition(0, -300 * delta);
		else if (INPUT->keyDown(DIK_DOWN))
			m_sprites->setOffPosition(0, 300 * delta);
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
