/*
	Copyright (c) 2013 bodguy http://blog.naver.com/bodguy

	Creator(s)    : bodguy
	Creation Date : 2014-02-18
	File Name     : TextureManager.h
	license		  : LGPL v3.0
	Purpose       : 
*/

#pragma once

namespace sidescroll
{
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();

		Texture *LoadTexture(std::string name, DWORD colorkey);
		bool ReleaseTexture(std::string name);

	private:
		std::map<std::string, Texture*> m_Textures;
	};
}
