#pragma once

class File
{
public:
	File(void) {}
	File(const char* pp, const char* r) {
		p = fopen(pp, r);
		if (p == 0) throw File_error(pp, r);
	}
	File(const std::string s, const char* r) {
		p = fopen(s.c_str(), r);
		if (p == 0) throw File_error(s.c_str(), r);
	}
	~File() { fclose(p); } //destructor

	const char* File_error(const char* s, const char* r) { return nullptr; }

private:
	FILE* p;
};