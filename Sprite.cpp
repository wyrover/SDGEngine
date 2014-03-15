#include "Precompiled.h"

namespace sidescroll
{
	Sprite::Sprite()
		:width(0), height(0), textureOffset(0.f, 0.f), textureScale(0.f, 0.f), position(0.f, 0.f)
	{
	}

	Sprite::Sprite(const std::string &filename)
		: width(0), height(0), textureOffset(0.f, 0.f), textureScale(32.f, 48.f), position(100.f, 100.f)
	{
		m_texture = MySingleton<Assets>::GetSingleton()->RequestTexture(filename);
		if (m_texture)
		{
			width = m_texture->width();
			height =  m_texture->height();
		}
	}

	Sprite::~Sprite()
	{
		if (m_texture)
		{
			m_texture->RemoveReference();
			m_texture = nullptr;
		}
	}

	void Sprite::Render()
	{
		Graphics::SetAlphatest(true);
		Graphics::BindTexture(m_texture);
		Graphics::RenderQuad(width, height, textureOffset, textureScale, position);
		Graphics::SetAlphatest(false);
		Graphics::BindTexture(nullptr);
		Graphics::RenderLineRect(-textureScale.x*0.5f + position.x, -textureScale.y*0.5f + position.y, textureScale.x, textureScale.y);
	}

	void Sprite::setOffPosition(float x, float y)
	{
		position.x += x;
		position.y += y;
	}

	void Sprite::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
}