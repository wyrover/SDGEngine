#include "Precompiled.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Init()
{
	m_texture = ENGINE->GRAPHICS()->LoadTexture("texture/desk.jpg", D3DXCOLOR(1,1,1,1));
}

void Renderer::Destroy()
{
	ENGINE->GRAPHICS()->ReleaseTexture("texture/desk.jpg");
}

void Renderer::Update(float delta)
{

}

void Renderer::Render()
{
	ENGINE->Sprite()->Draw(m_texture->texture(), nullptr, nullptr, nullptr, D3DXCOLOR(1,1,1,1));
}

EMessageResult Renderer::HandleMessage(const Message &msg)
{
	switch (msg.m_type)
	{
	case MT_OBJECT_CREATED:
		std::cout << "Renderer MT_OBJECT_CREATED" << std::endl;
		return MR_TRUE;
	case MT_UPDATE:
		std::cout << "Renderer MT_UPDATE" << std::endl;
		return MR_TRUE;
	}

	return MR_IGNORED;
}