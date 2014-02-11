#include "Precompiled.h"

Texture::Texture()
{
	ZeroMemory(&m_ImgInfo, sizeof(m_ImgInfo));
}

HRESULT Texture::LoadFromFile(LPDIRECT3DDEVICE9 pDev, std::string sFile, DWORD colorkey)
{
	assert(m_pTex == nullptr);
	m_pDev = pDev;
	DWORD dColorKey = colorkey;

	if (FAILED(D3DXCreateTextureFromFileEx(m_pDev, sFile.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		dColorKey, &m_ImgInfo, nullptr, &m_pTex)))
	{
		std::string errorMsg = "Could not open texture file : " + sFile + "\n";
		std::cout << errorMsg.c_str() << std::endl;
		Destroy();

		return E_FAIL;
	}

	m_strTexName = sFile;
	AddReference();

	return S_OK;
}

HRESULT Texture::LoadFromMemory(LPDIRECT3DDEVICE9 pDev, std::string szEntityName)
{
	AddReference();
	return S_OK;
}

void Texture::Destroy()
{
	if (m_pTex)
	{
		m_pTex->Release();
		m_pTex = nullptr;
	}
}

void Texture::AddReference()
{
	m_iRefCount++;
}

void Texture::ReleaseReference()
{
	m_iRefCount--;
	if (m_iRefCount == 0)
		Destroy();
}

int Texture::width()
{
	return m_ImgInfo.Width;
}

int Texture::height()
{
	return m_ImgInfo.Height;
}

void Texture::rect(RECT* pRc)
{
	pRc->left = 0;
	pRc->top = 0;
	pRc->right = m_ImgInfo.Width;
	pRc->bottom = m_ImgInfo.Height;
}

LPDIRECT3DTEXTURE9 Texture::texture()
{
	return m_pTex;
}
