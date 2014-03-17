#include "Precompiled.h"

namespace SDGEngine
{
	Asset::Asset(AssetType type)
		:m_iRefCount(0), m_type(type), m_isCached(false)
	{
	}

	void Asset::AddReference()
	{
		m_iRefCount++;
	}

	void Asset::RemoveReference()
	{
		m_iRefCount--;
		if (m_iRefCount == 0)
		{
			if (!m_isCached)
			{
				Unload();
				Singleton<Assets>::GetSingleton()->RemoveAsset(this);
			}
		}
	}

	std::string Asset::name()
	{
		return m_filename;
	}
}
