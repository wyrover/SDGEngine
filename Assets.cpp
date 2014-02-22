#include "Precompiled.h"

namespace sidescroll
{
	Assets *assets = nullptr;
	Assets::Assets()
	{
		assets = this;
	}

	Assets::~Assets()
	{
		assets = nullptr;
	}

	TextureAsset *Assets::RequestTexture(const std::string &filename)
	{
		TextureAsset *asset = nullptr;
		asset = (TextureAsset *)GetAssetByFilename(filename);

		if (!asset)
		{
			asset = new TextureAsset();
			if (asset->Load(filename))
			{
				StoreAsset(asset);
			}
			else
			{
				SDELETE(asset);
			}
		}

		if (asset)
			asset->AddReference();

		return asset;
	}

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
}
