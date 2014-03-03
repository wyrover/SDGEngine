#include "Precompiled.h"

namespace sidescroll
{
	Sprite::Sprite()
		:width(0), height(0), textureOffset(0.f, 0.f), textureScale(0.f, 0.f), position(500.f, 500.f)
	{
		textureScale.x = float(width);
		textureScale.y = float(height);
	}

	Sprite::Sprite(const std::string &filename)
		: width(0), height(0), textureOffset(0.f, 0.f), textureScale(0.f, 0.f), position(500.f, 500.f)
	{
		m_texture = ASSETS->RequestTexture(filename);
		if (m_texture)
		{
			width = m_texture->width();
			height = m_texture->height();
		}
		textureScale.x = float(width);
		textureScale.y = float(height);
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

		//Graphics::PushMatrix();
		//Graphics::Translate(position.x, position.y, 0.0f);
		//Graphics::Rotate(rotation, 0, 0, 1);
		//Graphics::PopMatrix();
		//Graphics::RenderLineRect(0, 0, width, height);
		//Graphics::RenderLine(Vector2(width*0.5f, -height*0.5f), Vector2(-width*0.5f, height*0.5f));
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