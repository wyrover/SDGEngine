#include "Precompiled.h"

namespace sidescroll
{
	XMLFileNode::XMLFileNode()
		:m_element(nullptr), m_iterator(nullptr)
	{

	}

	XMLFileNode::XMLFileNode(TiXmlElement *element)
		: m_element(element), m_iterator(nullptr)
	{
	}

	XMLFileNode::~XMLFileNode()
	{
		SDELETE(m_iterator);
	}

	XMLFileNode* XMLFileNode::FirstChildNode(const std::string &name)
	{
		if (m_iterator)
			m_iterator = new XMLFileNode(m_element->FirstChildElement(name));
		else
			m_iterator->m_element = m_element->FirstChildElement(name);

		if (m_iterator != nullptr && m_iterator->m_element == nullptr)
		{
			SDELETE(m_iterator);
		}

		return m_iterator;
	}

	XMLFileNode* XMLFileNode::NextChildNode(const std::string &name)
	{
		if (m_iterator)
		{
			if (m_iterator->m_element)
			{
				m_iterator->m_element = m_iterator->m_element->NextSiblingElement(name);
			}

			if (m_iterator->m_element == nullptr)
			{
				SDELETE(m_iterator);
			}
		}

		return m_iterator;
	}

	void XMLFileNode::Write(const std::string &name, const int &value)
	{
		m_element->SetAttribute(name, value);
	}

	void XMLFileNode::Write(const std::string &name, const float &value)
	{
		std::ostringstream os;
		os << value;
		m_element->SetAttribute(name, os.str());
	}

	void XMLFileNode::Write(const std::string &name, const std::string &value)
	{
		m_element->SetAttribute(name, value);
	}

	void XMLFileNode::Write(const std::string &name, const D3DXVECTOR2 &value)
	{
		std::ostringstream os;
		os << value.x << " " << value.y;
		m_element->SetAttribute(name, os.str());
	}

	void XMLFileNode::Write(const std::string &name, const D3DXCOLOR &value)
	{
		std::ostringstream os;
		os << value.r << " " << value.g << " " << value.b << " " << value.a;
		m_element->SetAttribute(name, os.str());
	}

	void XMLFileNode::Write(const std::string &name, const bool &value)
	{
		m_element->SetAttribute(name, (int)value);
	}

	void XMLFileNode::Read(const std::string &name, int &value)
	{
		if (m_element->Attribute(name))
		{
			std::istringstream read(*m_element->Attribute(name));
			read >> value;
		}
	}

	void XMLFileNode::Read(const std::string &name, float &value)
	{
		if (m_element->Attribute(name))
		{
			std::istringstream read(*m_element->Attribute(name));
			read >> value;
		}
	}

	void XMLFileNode::Read(const std::string &name, std::string &value)
	{
		if (m_element->Attribute(name))
		{
			value = *m_element->Attribute(name);
		}
	}

	void XMLFileNode::Read(const std::string &name, D3DXVECTOR2 &value)
	{
		if (m_element->Attribute(name))
		{
			std::istringstream read(*m_element->Attribute(name));
			read >> value.x >> value.y;
		}
	}

	void XMLFileNode::Read(const std::string &name, D3DXCOLOR &value)
	{
		if (m_element->Attribute(name))
		{
			std::string string = *m_element->Attribute(name);
			std::istringstream read(string);
			if (string.find('#') != std::string::npos)
			{
				// TODO: read hex color
			}
			else
			{
				read >> value.r >> value.g >> value.b >> value.a;
			}
		}
	}

	void XMLFileNode::Read(const std::string &name, bool &value)
	{
		if (m_element->Attribute(name))
		{
			std::istringstream read(*m_element->Attribute(name));
			read >> value;
		}
	}
}
