#pragma once

namespace sidescroll
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		HRESULT LoadFromFile(LPDIRECT3DDEVICE9 pDev, std::string &sFile, DWORD colorkey);
		HRESULT LoadFromMemory(LPDIRECT3DDEVICE9 pDev, std::string &szEntityName);

	private:
		void AddReference();
		void ReleaseReference();
		void Destroy();

	public:
		int width();
		int height();
		std::string &name() { return m_strTexName; }
		void rect(RECT* pRc);
		LPDIRECT3DTEXTURE9	texture();

	private:
		int					m_iRefCount = 0;
		std::string			m_strTexName;
		LPDIRECT3DDEVICE9	m_pDev = nullptr;
		D3DXIMAGE_INFO		m_ImgInfo;
		LPDIRECT3DTEXTURE9	m_pTex = nullptr;

		friend class TextureManager;
	};
}
