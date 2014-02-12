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
	
}

void TextComponent::Render()
{
	std::cout << "TextComponent Render" << std::endl;
}

EMessageResult TextComponent::HandleMessage(const Message &msg)
{
	switch (msg.m_type)
	{
	case MT_OBJECT_CREATED:
		std::cout << "TextComponent MT_OBJECT_CREATED" << std::endl;
		return MR_TRUE;
	case MT_UPDATE:
		std::cout << "TextComponent MT_UPDATE" << std::endl;
		return MR_TRUE;
	}

	return MR_IGNORED;
}