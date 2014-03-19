#include "Precompiled.h"

namespace SDGEngine
{
	Sprite::Sprite()
	{

	}

	void Sprite::Init()
	{

	}

	void Sprite::Destroy()
	{
		if (m_texture)
		{
			m_texture->RemoveReference();
			m_texture = NULL;
		}
	}

	void Sprite::Render()
	{
		if (m_texture)
		{
			Graphics::SetAlphatest(true);
			Graphics::BindTexture(m_texture);
			Graphics::RenderQuad(width, height, textureOffset, textureScale, m_tx.pos);
			Graphics::SetAlphatest(false);
			Graphics::BindTexture(NULL);
			Graphics::RenderLineRect(textureOffset.x + m_tx.pos.x, textureOffset.y + m_tx.pos.y, textureScale.x, textureScale.y);
		}
	}

	void Sprite::Update(float delta)
	{

	}

	EMessageResult Sprite::HandleMessage(const Message &msg)
	{
		switch (msg.m_type)
		{
		case MT_OBJECT_CREATED:
			name = static_cast<const char *>(msg.m_data);
			m_texture = Singleton<Assets>::GetSingleton()->RequestTexture(name);
			if (m_texture)
			{
				width = m_texture->width();
				height = m_texture->height();
			}
			return MR_TRUE;
		case MT_SET_TEXSCALE:
			textureScale = *static_cast<D3DXVECTOR2 *>(msg.m_data);
			return MR_TRUE;
		case MT_SET_TEXOFFSET:
			textureOffset = *static_cast<D3DXVECTOR2 *>(msg.m_data);
			return MR_TRUE;
		case MT_SET_POSITION:
			m_tx.pos = *static_cast<D3DXVECTOR2 *>(msg.m_data);
			return MR_TRUE;
		case MT_SET_ZORDER:
			m_tx.zorder = *static_cast<int *>(msg.m_data);
			return MR_TRUE;
		}

		return MR_IGNORED;
	}
}