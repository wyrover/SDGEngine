#include "Precompiled.h"

namespace SDGEngine
{
	Assets::Assets()
	{
		SetContentPath(GetDefaultContentPath());
	}

	Assets::~Assets()
	{

	}

	std::string Assets::GetDefaultContentPath()
	{
		return "content/";
	}

	TextureAsset *Assets::RequestTexture(const std::string &filename)
	{
		TextureAsset *asset = NULL;
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
			std::cout << asset->m_filename << ": RefCount (" << asset->m_iRefCount << ")" << std::endl;
		}

		return asset;
	}

	FontAsset *Assets::RequestFont(const std::string &filename, int size)
	{
		FontAsset *asset = NULL;
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
			std::cout << asset->m_filename << ": RefCount (" << asset->m_iRefCount << ")" << std::endl;
		}

		return asset;
	}

	//AudioAsset *Assets::RequestAudio(const std::string &filename, FMOD_MODE mode)
	//{
	//	AudioAsset *asset = NULL;
	//	std::string name = GetContentPath() + filename;

	//	// check to see if we have one stored already
	//	asset = (AudioAsset*)GetAssetByFilename(name);

	//	// if not, load it and store it
	//	if (!asset)
	//	{
	//		asset = new AudioAsset();
	//		if (asset->Load(name, mode))
	//		{
	//			StoreAsset(asset);
	//			std::cout << asset->m_filename << ": Load" << std::endl;
	//		}
	//		else
	//		{
	//			SDELETE(asset);
	//		}
	//	}

	//	if (asset)
	//	{
	//		asset->AddReference();
	//		std::cout << asset->m_filename << ": RefCount (" << asset->m_iRefCount << ")" << std::endl;
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
		SDELETE(asset);
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

		return NULL;
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
