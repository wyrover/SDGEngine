#pragma once

namespace sidescroll
{
	class XMLFile : public File
	{
	public:
		XMLFile(TiXmlElement *);
		virtual ~XMLFile();

		virtual void Write(const std::string &name, const int &value) override;
		virtual void Write(const std::string &name, const float &value) override;
		virtual void Write(const std::string &name, const std::string &value) override;
		virtual void Write(const std::string &name, const D3DXVECTOR2 &value) override;
		virtual void Write(const std::string &name, const DWORD &value) override;
		virtual void Write(const std::string &name, const bool &value) override;

		virtual void Read(const std::string &name, int &value) override;
		virtual void Read(const std::string &name, float &value) override;
		virtual void Read(const std::string &name, std::string &value) override;
		virtual void Read(const std::string &name, D3DXVECTOR2 &value) override;
		virtual void Read(const std::string &name, DWORD &value) override;
		virtual void Read(const std::string &name, bool &value) override;
	};
}
