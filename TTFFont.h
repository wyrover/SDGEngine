#pragma once

namespace SDGEngine
{
	class TTFFont : public Singleton<TTFFont>
	{
	public:
		explicit TTFFont(int width);
		virtual ~TTFFont();

		int Lock();
		void UnLock();

		struct Glyph
		{
			FT_Face face;
			char chr;
			int size;
			bool operator < (const Glyph& g) const
			{
				if (face < g.face) return true;
				else if (face > g.face) return false;
				if (chr < g.chr) return true;
				else if (chr > g.chr) return false;
				if (size < g.size) return true;
				return false;
			}
		};

		struct GlyphData
		{
			float u, v, w, h;
			int left, top;
			int bmW, bmH;
			int advX, advY;
			int height;
			int use;
		};

		bool IsOccupied(int x, int y, int w, int h) const;
		void Fill(int x, int y, int w, int h, char d = 1);
		std::pair<int, int> Find(int w, int h) const;
		TTFFont::GlyphData GetGlyph(FT_Face face, char chr, int size);
		std::string PrepareGlyph(FT_Face face, const char *str, int len, int size);
		void CleanUp();
		void NewFrame();
		const char& MapAt(int x, int y) const { return m_used[x + y*(m_width / 4)]; }
		char& MapAt(int x, int y) { return m_used[x + y*(m_width / 4)]; }
		FT_Library library() const { return m_library; }
		TextureAsset *texture() const { m_tex; }

	private:
		FT_Library m_library;
		int m_width;
		TextureAsset *m_tex;
		D3DLOCKED_RECT m_lockedrect;
		std::vector<char> m_used;
		std::map<Glyph, GlyphData> m_data;
		DISALLOW_COPY_AND_ASSIGN(TTFFont);
	};
}
