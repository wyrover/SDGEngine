/*
	Copyright (c) 2013 bodguy http://blog.naver.com/bodguy

	Creator(s)    : bodguy
	Creation Date : 2014-02-20
	File Name     : Assets.h
	license		  : LGPL v3.0
	Purpose       :
*/

#pragma once

namespace sidescroll
{
	class TextureAsset;
	class Assets;
	extern Assets *ASSETS;
	class Assets
	{
	public:
		Assets();
		~Assets();

		TextureAsset *RequestTexture(const std::string &filename);
		//FontAsset *RequestFont(const std::string &filename, float size, int textureWidth = -1, int textureHeight = -1);
		//AudioAsset *RequestAudio(const std::string &filename, bool streamFromDisk = false, std::string decodeString = "");

		void RemoveAsset(Asset *asset);
		void StoreAsset(Asset *asset);
		Asset *GetAssetByFilename(const std::string &filename);

	private:
		std::list<Asset *> m_assets;
	};
}
