#include "Precompiled.h"

namespace sidescroll
{
	File::File(void)
	{

	}

	File::File(const char* pp, const char* r)
	{
		p = fopen(pp, r);
		if (p == 0) throw File_error(pp, r);
	}

	File::File(const std::string &s, const char* r)
	{
		p = fopen(s.c_str(), r);
		if (p == 0) throw File_error(s.c_str(), r);
	}

	File::~File()
	{
		fclose(p);
	}

	const char* File::File_error(const char* s, const char* r)
	{
		std::stringstream ss;
		ss << "does not open: " << s << " with " << r << "operation" << std::endl;
		return ss.str().c_str();
	}
}
