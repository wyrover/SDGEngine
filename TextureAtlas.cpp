#include "Precompiled.h"

namespace sidescroll
{
	TextureAtlasEntry::TextureAtlasEntry()
		: x(0), y(0), width(0), height(0), textureAtlas(nullptr)
	{

	}

	TextureAtlasEntry::TextureAtlasEntry(TextureAtlas *textureAtlas)
		: x(0), y(0), width(0), height(0), textureAtlas(textureAtlas)
	{

	}
	
	void TextureAtlasEntry::Save(XMLFile *file)
	{
		file->Write("name", name);

		file->Write("x", x);
		file->Write("y", y);
		file->Write("width", width);
		file->Write("height", height);
	}

	void TextureAtlasEntry::Load(XMLFile *file)
	{
		file->Read("name", name);

		file->Read("x", x);
		file->Read("y", y);
		file->Read("width", width);
		file->Read("height", height);
	}

	D3DXVECTOR2 TextureAtlasEntry::TextureOffset()
	{
		return D3DXVECTOR2(x / float(textureAtlas->m_width), y / float(textureAtlas->m_height));
	}
	
	D3DXVECTOR2 TextureAtlasEntry::TextureScale()
	{
		return D3DXVECTOR2(width / float(textureAtlas->m_width), height / float(textureAtlas->m_height));
	}
	
	int TextureAtlasEntry::Width()
	{
		return int(width * textureAtlas->m_scale);
	}

	int TextureAtlasEntry::Height()
	{
		return int(height * textureAtlas->m_scale);
	}

	TextureAtlas::TextureAtlas()
		: m_width(0), m_height(0), m_scale(1.0f)
	{
	}

	TextureAtlas::~TextureAtlas()
	{
		for (auto i : m_entries)
		{
			SDELETE(i.second);
		}
		m_entries.clear();
	}

	TextureAtlasEntry* TextureAtlas::GetEntryByName(const std::string &name)
	{
		return m_entries[name];
	}

	void TextureAtlas::Save(TiXmlDocument *document)
	{
		TiXmlElement xmlTextureAtlas("TextureAtlas");

		XMLFile xmlOut(&xmlTextureAtlas);
		xmlOut.Write("image", m_image);
		xmlOut.Write("width", m_width);
		xmlOut.Write("height", m_height);
		xmlOut.Write("scale", m_scale);

		for (auto i : m_entries)
		{
			TextureAtlasEntry *textureAtlasEntry = i.second;

			TiXmlElement xmlAtlasEntry("TextureAtlasEntry");
			XMLFile xmlFileNode(&xmlAtlasEntry);
			textureAtlasEntry->Save(&xmlFileNode);

			xmlTextureAtlas.InsertEndChild(xmlAtlasEntry);
		}

		document->InsertEndChild(xmlTextureAtlas);
	}

	void TextureAtlas::Load(TiXmlElement *element)
	{
		XMLFile xmlFileNodeTextureAtlas(element);
		xmlFileNodeTextureAtlas.Read("image", m_image);
		xmlFileNodeTextureAtlas.Read("width", m_width);
		xmlFileNodeTextureAtlas.Read("height", m_height);
		xmlFileNodeTextureAtlas.Read("scale", m_scale);

		TiXmlElement *xmlAtlasEntry = element->FirstChildElement("TextureAtlasEntry");
		while (xmlAtlasEntry)
		{
			XMLFile xmlFileNode(xmlAtlasEntry);

			TextureAtlasEntry *textureAtlasEntry = new TextureAtlasEntry(this);
			textureAtlasEntry->Load(&xmlFileNode);
			if (textureAtlasEntry->name != "")
				m_entries[textureAtlasEntry->name] = textureAtlasEntry;

			xmlAtlasEntry = xmlAtlasEntry->NextSiblingElement("TextureAtlasEntry");
		}
	}

	std::string TextureAtlas::GetImageName()
	{
		return m_image;
	}
}
