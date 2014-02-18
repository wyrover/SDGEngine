#include "Precompiled.h"

namespace sidescroll
{
	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Init()
	{
		
	}

	void Renderer::Destroy()
	{
		ENGINE->GRAPHICS()->ReleaseTexture(m_texture->name());
	}

	void Renderer::Update(float delta)
	{

	}

	void Renderer::Render()
	{
		ENGINE->Sprite()->Draw(m_texture->texture(), nullptr, nullptr, nullptr, D3DXCOLOR(1, 1, 1, 1));
	}

	EMessageResult Renderer::HandleMessage(const Message &msg)
	{
		switch (msg.m_type)
		{
		case MT_OBJECT_CREATED:
			m_texture = ENGINE->GRAPHICS()->LoadTexture(std::string(static_cast<char *>(msg.m_data)), D3DXCOLOR(1, 1, 1, 1));
			return MR_TRUE;
		case MT_UPDATE:
			return MR_TRUE;
		}

		return MR_IGNORED;
	}
}
