#include "Precompiled.h"

namespace SDGEngine
{
	TextureAsset::TextureAsset()
		:Asset(ASSET_TEXTURE)
	{
	}

	TextureAsset::~TextureAsset()
	{

	}

	bool TextureAsset::LoadDynamic(int w, int h)
	{
		if (FAILED(D3DXCreateTexture(Singleton<Engine>::GetSingleton()->Device(), w, h, 1, 0, 
			D3DFMT_A8B8G8R8, D3DPOOL_MANAGED, &m_texture))) {
			std::string errorMsg = "Could not create empty texture\n";
			std::cout << errorMsg.c_str() << std::endl;
			return false;
		}

		return true;
	}

	bool TextureAsset::Load(const std::string data)
	{
		m_filename = data;

		if (FAILED(D3DXCreateTextureFromFileEx(Singleton<Engine>::GetSingleton()->Device(), data.c_str(),
			D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
			m_color, &m_texturInfo, NULL, &m_texture)))
		{
			std::string errorMsg = "Could not open texture file : " + data + "\n";
			std::cout << errorMsg.c_str() << std::endl;
			return false;
		}

		return true;
	}

	unsigned int TextureAsset::width()
	{
		return m_texturInfo.Width;
	}

	unsigned int TextureAsset::height()
	{
		return m_texturInfo.Height;
	}

	IDirect3DTexture9 *TextureAsset::texture()
	{
		return m_texture;
	}

	void TextureAsset::CopyRect(RECT *dest)
	{
		dest->left = 0;
		dest->top = 0;
		dest->right = m_texturInfo.Width;
		dest->bottom = m_texturInfo.Height;
	}

	void TextureAsset::Reload()
	{
		if (m_filename.length() != 0)
		{
			Unload();
			Load(m_filename);
		}
	}

	void TextureAsset::Unload()
	{
		SRELEASE(m_texture);
	}
}
