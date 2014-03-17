/*
	Copyright (c) 2013 bodguy http://blog.naver.com/bodguy

	Creator(s)    : bodguy
	Creation Date : 2014-02-20
	File Name     : Asset.h
	license		  : LGPL v3.0
	Purpose       :
*/

#pragma once

namespace sidescroll
{
	enum AssetType
	{
		ASSET_UNDEFINED,
		ASSET_TEXTURE,
		ASSET_AUDIO,
		ASSET_FONT
	};

	class Asset
	{
	public:
		explicit Asset(AssetType type);
		virtual ~Asset() {}

		void AddReference();
		void RemoveReference();
		virtual void Reload() = 0;

		std::string name();

	protected:
		virtual void Unload() = 0;

	protected:
		std::string m_filename;
		AssetType m_type;
		int m_iRefCount;
		bool m_isCached;

		friend class Assets;
	};
}
