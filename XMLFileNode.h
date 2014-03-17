#pragma once

namespace SDGEngine
{
	class XMLFileNode
	{
	public:
		XMLFileNode();
		XMLFileNode(TiXmlElement *);
		virtual ~XMLFileNode();

		void Write(const std::string &name, const int &value);
		void Write(const std::string &name, const float &value);
		void Write(const std::string &name, const std::string &value);
		void Write(const std::string &name, const D3DXVECTOR2 &value);
		void Write(const std::string &name, const D3DXCOLOR &value);
		void Write(const std::string &name, const bool &value);

		void Read(const std::string &name, int &value);
		void Read(const std::string &name, float &value);
		void Read(const std::string &name, std::string &value);
		void Read(const std::string &name, D3DXVECTOR2 &value);
		void Read(const std::string &name, D3DXCOLOR &value);
		void Read(const std::string &name, bool &value);

		XMLFileNode* FirstChildNode(const std::string &name);
		XMLFileNode* NextChildNode(const std::string &name);

	private:
		TiXmlElement *m_element;
		XMLFileNode *m_iterator;
	};
}
