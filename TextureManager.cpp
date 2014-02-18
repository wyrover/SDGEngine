#include "Precompiled.h"

namespace sidescroll
{
	TextureManager::TextureManager()
	{
	}

	TextureManager::~TextureManager()
	{
		for (auto i : m_Textures)
		{
			SDELETE(i.second);
		}
	}

	Texture *TextureManager::LoadTexture(std::string name, DWORD colorkey)
	{
		auto iter = m_Textures.find(name);
		if (iter != m_Textures.end())
			return iter->second;

		Texture* texture = new Texture;
		assert(texture);

		if (FAILED(texture->LoadFromFile(ENGINE->device(), name, colorkey)))
		{
			SDELETE(texture);
			throw std::logic_error("TextureManager::LoadFromFile() failed!");
		}

		m_Textures[name] = texture;
		return texture;
	}

	bool TextureManager::ReleaseTexture(std::string strTextName)
	{
		bool bFound = false;
		auto iter = m_Textures.find(strTextName);
		if (iter != m_Textures.end())
		{
			// find
			bFound = true;
			iter->second->ReleaseReference();
			SDELETE(iter->second);
			m_Textures.erase(iter);
		}

		return bFound;
	}
}
