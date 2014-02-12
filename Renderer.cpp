#include "Precompiled.h"

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

}

void Renderer::Update(float delta)
{

}

void Renderer::Render()
{
	std::cout << "Renderer Render" << std::endl;
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