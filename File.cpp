#include "Precompiled.h"

namespace SDGEngine
{
	File::File()
		: fp(NULL)
	{
	}

	File::File(FILE *file)
		: fp(file)
	{
	}

	File::~File()
	{
		Clear();
	}

	void File::Open(const char *name, OpenType access_type)
	{
		switch (access_type)
		{
		case OpenType::Read:
			fp = fopen(name, "r");
			break;
		case OpenType::Write:
			fp = fopen(name, "w");
			break;
		case OpenType::Append:
			fp = fopen(name, "a");
			break;
		}
		assert(fp);
	}

	void File::Close(void)
	{
		if (fp)
			fclose(fp);
	}

	void File::Clear(void)
	{
		Close();
	}

	void File::Write(const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		vfprintf(fp, format, args);
		va_end(args);
	}

	void File::Read(const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		vfscanf(fp, format, args);
		va_end(args);
	}

	std::string File::GetLine(void)
	{
		std::string temp;

		char c;

		for (;;)
		{
			c = static_cast<char>(fgetc(fp));
			if (feof(fp))
				break;
			else if (c == '\n')
				break;
			temp += c;
		}

		return std::move(temp);
	}

	std::string File::GetLine(char delim)
	{
		std::string temp;

		char c;

		for (;;)
		{
			c = static_cast<char>(fgetc(fp));
			if (feof(fp))
				break;
			else if (c == delim)
				break;
			temp += c;
		}

		return std::move(temp);
	}

	std::string File::GetLine(const char *delims)
	{
		std::string temp;

		char c;

		for (;;)
		{
			c = static_cast<char>(fgetc(fp));
			if (feof(fp))
				break;
			for (const char *temp_delim = delims; temp_delim; ++temp_delim)
				if (c == *temp_delim)
					break;
			temp += c;
		}

		return std::move(temp);
	}

	void File::SeekFromBeginOfFile(int offset)
	{
		fseek(fp, offset, SEEK_SET);
	}

	void File::SeekFromEndOfFile(int offset)
	{
		fseek(fp, offset, SEEK_END);
	}

	void File::SeekByOffset(int offset)
	{
		fseek(fp, offset, SEEK_CUR);
	}

	bool File::Validate(void) const
	{
		return fp && !feof(fp) ? true : false;
	}
}
