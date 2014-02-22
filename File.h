#pragma once

namespace sidescroll
{
	class File
	{
	public:
		File(void);
		File(const char* pp, const char* r);
		File(const std::string s, const char* r);
		~File();

		const char* File_error(const char* s, const char* r);

		virtual void Write(const std::string &name, const int &value) = 0;
		virtual void Write(const std::string &name, const float &value) = 0;
		virtual void Write(const std::string &name, const std::string &value) = 0;
		virtual void Write(const std::string &name, const D3DXVECTOR2 &value) = 0;
		virtual void Write(const std::string &name, const DWORD &value) = 0;
		virtual void Write(const std::string &name, const bool &value) = 0;

		virtual void Read(const std::string &name, int &value) = 0;
		virtual void Read(const std::string &name, float &value) = 0;
		virtual void Read(const std::string &name, std::string &value) = 0;
		virtual void Read(const std::string &name, D3DXVECTOR2 &value) = 0;
		virtual void Read(const std::string &name, DWORD &value) = 0;
		virtual void Read(const std::string &name, bool &value) = 0;

	private:
		FILE* p;
	};
}
