#include "Precompiled.h"

namespace sidescroll
{
	FontAsset::FontAsset()
		: Asset(ASSET_FONT)
	{
	}

	FontAsset::~FontAsset()
	{
		Unload();
	}

	bool FontAsset::Load(const std::string data, int size, D3DCOLOR color)
	{
		m_filename = data;
		m_fontSize = size;
		m_fontColor = color;

		if (FAILED(D3DXCreateFont(Singleton<Engine>::GetSingleton()->Device(), m_fontSize, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_filename.c_str(), &m_Font)))
		{
			std::cout << "can not create Font: " << m_filename.c_str() << std::endl;
			return false;
		}

		return true;
	}

	void FontAsset::Reload()
	{
		if (m_filename.length() != 0)
		{
			Unload();
			Load(m_filename, m_fontSize);
		}
	}

	void FontAsset::Unload()
	{
		SRELEASE(m_Font);
	}
}
