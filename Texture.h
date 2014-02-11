#pragma once

class Texture
{
public:
	Texture();
	~Texture(){ Destroy(); }

	void AddReference();
	void ReleaseReference();

private:
	HRESULT LoadFromFile(LPDIRECT3DDEVICE9 pDev, std::string sFile, DWORD colorkey);
	HRESULT LoadFromMemory(LPDIRECT3DDEVICE9 pDev, std::string szEntityName);
	void Destroy();

public:
	int width();
	int height();
	void rect(RECT* pRc);
	LPDIRECT3DTEXTURE9	texture();

private:
	int					m_iRefCount = 0;
	std::string			m_strTexName;
	LPDIRECT3DDEVICE9	m_pDev = nullptr;
	D3DXIMAGE_INFO		m_ImgInfo;
	LPDIRECT3DTEXTURE9	m_pTex = nullptr;
};
