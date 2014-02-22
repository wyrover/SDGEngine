#pragma once

namespace sidescroll
{
	class File;
	class TextureAtlas;
	class TextureAtlasEntry
	{
	public:
		TextureAtlasEntry();
		TextureAtlasEntry(TextureAtlas *textureAtlas);

		void Save(File &file);
		void Load(File &file);

		D3DXVECTOR2 TextureOffset();
		D3DXVECTOR2 TextureScale();
		int Width();
		int Height();

	private:
		std::string name;
		int x, y, width, height;
		TextureAtlas *textureAtlas;
	};

	class TextureAtlas
	{
	public:
		TextureAtlas();
		~TextureAtlas();

		TextureAtlasEntry* GetEntryByName(const std::string &name);
		void Save(TiXmlDocument *document);
		void Load(TiXmlElement *element);
		std::string GetImageName();

	private:
		std::string m_image;
		int m_width, m_height;
		float m_scale;
		std::map<std::string, TextureAtlasEntry *> m_entries;
		friend class TextureAtlasEntry;
	};
}
