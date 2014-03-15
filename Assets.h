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
	class Asset;
	class AudioAsset;
	class TextureAsset;
	class FontAsset;
	class Assets : public MySingleton<Assets>
	{
	public:
		Assets();
		~Assets();

		TextureAsset *RequestTexture(const std::string &filename);
		FontAsset *RequestFont(const std::string &filename, int size);
		AudioAsset *RequestAudio(const std::string &filename, FMOD_MODE mode = FMOD_LOOP_OFF);

		void RemoveAsset(Asset *asset);
		void StoreAsset(Asset *asset);
		Asset *GetAssetByFilename(const std::string &filename);
		void SetContentPath(const std::string &contentPath);
		const std::string &GetContentPath();
		std::string GetDefaultContentPath();

	private:
		std::list<Asset *> m_assets;
		std::string m_contentPath;
	};
}
