#include "Precompiled.h"

namespace sidescroll
{
	Sprite::Sprite()
		:width(0), height(0), textureOffset(), textureScale()
	{
	}

	Sprite::Sprite(const std::string &filename)
		: width(0), height(0), textureOffset(), textureScale()
	{
		m_texture = ASSETS->RequestTexture(filename);
		if (m_texture)
		{
			width = m_texture->width();
			height = m_texture->height();
		}
		m_bounds = new Bounds(D3DXVECTOR2(500.f, 500.f), D3DXVECTOR2(width, height));
	}

	Sprite::~Sprite()
	{
		if (m_texture)
		{
			m_texture->RemoveReference();
			m_texture = nullptr;
		}
		SDELETE(m_bounds);
	}

	void Sprite::Render()
	{
		Graphics::SetAlphatest(true);
		Graphics::BindTexture(m_texture);
		Graphics::RenderBox(m_bounds->getMin(), m_bounds->getMax());
		Graphics::SetAlphatest(false);
		//Graphics::PushMatrix();

		//Graphics::Translate(position.x, position.y, 0.0f);
		//Graphics::Rotate(rotation, 0, 0, 1);
		//Graphics::BindTexture(texture);
		//Graphics::SetBlend(blend);

		//if (Debug::showBounds && entity->IsDebugLayer())
		//{
		//	if (Debug::selectedEntity == entity)
		//	{
		//		Color copyColor = entity->color;
		//		copyColor.a *= 0.8f;
		//		Graphics::SetColor(copyColor);
		//	}
		//	else if (Debug::selectedEntity != NULL && Debug::selectedEntity->GetLayer() > entity->GetLayer())
		//	{
		//		Color copyColor = entity->color;
		//		copyColor.a *= 0.6f;
		//		Graphics::SetColor(copyColor);
		//	}
		//}

		//Graphics::RenderQuad(width, height, textureOffset, textureScale);

		//Graphics::PopMatrix();


		//// show bounds, for editor/selection purposes
		//if ((Debug::showBounds || Debug::selectedEntity == entity) && entity->IsDebugLayer())
		//{
		//	Graphics::PushMatrix();
		//	Graphics::Translate(position.x, position.y, 0.0f);

		//	if (Debug::selectedEntity == entity)
		//		Graphics::SetColor(Color::orange);
		//	else
		//		Graphics::SetColor(Color(0.9f, 0.9f, 1.0f, 0.25f));

		//	Graphics::BindTexture(NULL);
		//	Graphics::RenderLineRect(0, 0, width, height);

		//	if (Debug::selectedEntity != entity)
		//	{
		//		Graphics::RenderLine(Vector2(-width*0.5f, -height*0.5f), Vector2(width*0.5f, height*0.5f));
		//		Graphics::RenderLine(Vector2(width*0.5f, -height*0.5f), Vector2(-width*0.5f, height*0.5f));
		//	}
		//	else
		//	{
		//		Graphics::SetColor(Color::orange - Color(0, 0, 0, 0.5f));
		//		Graphics::RenderLine(Vector2(-width*0.5f, -height*0.5f), Vector2(width*0.5f, height*0.5f));
		//		Graphics::RenderLine(Vector2(width*0.5f, -height*0.5f), Vector2(-width*0.5f, height*0.5f));
		//	}

		//	Graphics::PopMatrix();
		//}
	}

	void Sprite::setOffPosition(float x, float y)
	{
		m_bounds->getMin().x += x;
		m_bounds->getMin().y += y;
		m_bounds->getMax().x += x;
		m_bounds->getMax().y += y;
	}

	void Sprite::setPosition(float x, float y)
	{
		m_bounds->getMin().x = x;
		m_bounds->getMin().y = y;
		m_bounds->getMax().x = x;
		m_bounds->getMax().y = y;
	}
}