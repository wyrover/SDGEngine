#include "Precompiled.h"

namespace sidescroll
{
	Assets *ASSETS = nullptr;
	Assets::Assets()
	{
		ASSETS = this;
		SetContentPath(GetDefaultContentPath());
	}

	Assets::~Assets()
	{
		ASSETS = nullptr;
	}

	std::string Assets::GetDefaultContentPath()
	{
		return "content/";
	}

	TextureAsset *Assets::RequestTexture(const std::string &filename)
	{
		TextureAsset *asset = nullptr;
		std::string name = GetContentPath() + filename;
		asset = (TextureAsset *)GetAssetByFilename(name);

		if (!asset)
		{
			asset = new TextureAsset();
			if (asset->Load(name))
			{
				StoreAsset(asset);
				std::cout << asset->m_filename << ": Load" << std::endl;
			}
			else
			{
				SDELETE(asset);
			}
		}

		if (asset)
		{
			asset->AddReference();
			std::cout << asset->m_filename << ": addReference (" << asset->m_iRefCount << ")" << std::endl;
		}

		return asset;
	}

	FontAsset *Assets::RequestFont(const std::string &filename, int size)
	{
		FontAsset *asset = nullptr;
		std::string name = filename; // GetContentPath() + filename;
		asset = (FontAsset *)GetAssetByFilename(name);

		if (!asset)
		{
			asset = new FontAsset();
			if (asset->Load(name, size))
			{
				StoreAsset(asset);
				std::cout << asset->m_filename << ": Load" << std::endl;
			}
			else
			{
				SDELETE(asset);
			}
		}

		if (asset)
		{
			asset->AddReference();
			std::cout << asset->m_filename << ": addReference (" << asset->m_iRefCount << ")" << std::endl;
		}

		return asset;
	}

	//AudioAsset *Assets::RequestAudio(const std::string &filename, bool streamFromDisk = false, std::string decodeString = "")
	//{
	//	AudioAsset *asset = NULL;
	//	std::string fullFilename = instance->contentPath + filename;

	//	//Debug::Log("instance->contentPath + filename: " + fullFilename);

	//	// check to see if we have one stored already
	//	asset = (AudioAsset*)instance->GetAssetByFilename(fullFilename);

	//	// if not, load it and store it
	//	if (!asset)
	//	{
	//		asset = new AudioAsset();
	//		asset->SetDecodeString(decodeString);
	//		asset->Load(fullFilename, streamFromDisk);

	//		// Return NULL if there was no asset...
	//		if (!asset->GetDataSize()){
	//			delete asset;
	//			return NULL;
	//		}

	//		instance->StoreAsset((Asset*)asset);
	//	}

	//	if (asset)
	//	{
	//		asset->AddReference();
	//	}

	//	// return what we found
	//	return asset;
	//}

	void Assets::StoreAsset(Asset *asset)
	{
		m_assets.push_back(asset);
	}

	void Assets::RemoveAsset(Asset *asset)
	{
		m_assets.remove(asset);
	}

	Asset *Assets::GetAssetByFilename(const std::string &filename)
	{
		for (auto i : m_assets)
		{
			if (i->m_filename == filename)
			{
				return i;
			}
		}

		return nullptr;
	}

	void Assets::SetContentPath(const std::string &contentPath)
	{
		m_contentPath = contentPath;
	}
	
	const std::string &Assets::GetContentPath()
	{
		return m_contentPath;
	}
}
