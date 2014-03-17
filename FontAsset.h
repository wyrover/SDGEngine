#pragma once

namespace sidescroll
{
	class FontAsset : public Asset
	{
	public:
		FontAsset();
		virtual ~FontAsset();

		bool Load(const std::string data, int size, D3DCOLOR color = D3DXCOLOR(0, 0, 0, 1));
		virtual void Reload() override;
		virtual void Unload() override;

		ID3DXFont* getFont() const { return m_Font; }
		DWORD getColor() const { return m_fontColor; }

	private:
		ID3DXFont* m_Font;
		int m_fontSize;
		DWORD m_fontColor;
	};
}
