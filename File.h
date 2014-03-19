#pragma once

namespace SDGEngine
{
	enum OpenType
	{
		Read,  // Read only
		Write, // Clear file contents
		Append // Write to end of file
	};
	class File
	{
	public:
		File();
		File(FILE *file);
		~File();

		void Open(const char *name, OpenType accessType = OpenType::Read);
		void Close(void); // Close file pointer
		void Clear(void); // Close file pointer (if open) and clear file name
		void Write(const char *format, ...);
		void Read(const char *format, ...);
		std::string GetLine(void);        // Retrieve one line delimited by '\n'
		std::string GetLine(char delim);  // Retrieve one line delimited by delim
		std::string GetLine(const char *delims);  // Retrieve one line delimited by chars within delims

		void SeekFromBeginOfFile(int offset);
		void SeekFromEndOfFile(int offset);
		void SeekByOffset(int offset);

		bool Validate(void) const;

	private:
		FILE *fp; // Pointer to file
	};
}
