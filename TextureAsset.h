#pragma once

namespace sidescroll
{
	class TextureAsset : public Asset
	{
	public:
		TextureAsset();
		virtual ~TextureAsset();

		bool Load(const std::string data);
		unsigned int width();
		unsigned int height();
		IDirect3DTexture9 *texture();
		void CopyRect(RECT *dest);
		virtual void Reload() override;
		virtual void Unload() override;

	private:
		D3DXIMAGE_INFO m_texturInfo;
		IDirect3DTexture9 *m_texture = nullptr;
		unsigned long m_color;
	};
}
