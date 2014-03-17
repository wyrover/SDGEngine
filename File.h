#pragma once

namespace SDGEngine
{
	class File
	{
	public:
		File(void);
		File(const char* pp, const char* r);
		File(const std::string &s, const char* r);
		~File();

		const char* File_error(const char* s, const char* r);

	private:
		FILE* p;
	};
}
