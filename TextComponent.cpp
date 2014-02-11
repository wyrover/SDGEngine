#include "Precompiled.h"

TextComponent::TextComponent()
{
}

TextComponent::~TextComponent()
{
}

void TextComponent::Init()
{
	std::cout << text.c_str() << std::endl;
}

void TextComponent::Destroy()
{

}

void TextComponent::Update(float delta)
{
	std::cout << "Update" << std::endl;
}

void TextComponent::Render()
{
	std::cout << "Render" << std::endl;
}

EMessageResult TextComponent::HandleMessage(const Message &msg)
{
	switch (msg.m_type)
	{
	case MT_OBJECT_CREATED:
		std::cout << "MT_OBJECT_CREATED" << std::endl;
		return MR_TRUE;
	case MT_UPDATE:
		std::cout << "MT_UPDATE" << std::endl;
		return MR_TRUE;
	}

	return MR_IGNORED;
}