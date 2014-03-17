#include "Precompiled.h"

namespace SDGEngine
{
	Animation::Animation()
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Destroy()
	{
		for (auto i : m_clips)
		{
			SDELETE(i.second);
		}
	}

	void Animation::Save(TiXmlDocument *document)
	{
		TiXmlElement xmlAnimation("Animation");

		XMLFileNode xmlOut(&xmlAnimation);
		xmlOut.Write("image", image);
		xmlOut.Write("width", width);
		xmlOut.Write("height", height);
		xmlOut.Write("autoplay", m_playAutomatically);

		for (auto i : m_clips)
		{
			AnimationClip *clip = i.second;

			TiXmlElement xmlClip("AnimationClip");
			XMLFileNode xmlFileNode(&xmlClip);
			clip->Save(&xmlFileNode);

			xmlAnimation.InsertEndChild(xmlClip);
		}

		document->InsertEndChild(xmlAnimation);
	}

	void Animation::Load(TiXmlElement *element)
	{
		XMLFileNode xmlIn(element);
		xmlIn.Read("image", image);
		xmlIn.Read("width", width);
		xmlIn.Read("height", height);
		xmlIn.Read("autoplay", m_playAutomatically);

		TiXmlElement *xmlAnimation = element->FirstChildElement("AnimationClip");
		while (xmlAnimation)
		{
			XMLFileNode xmlFileNode(xmlAnimation);

			AnimationClip *clip = new AnimationClip();
			clip->Load(&xmlFileNode);
			if (clip->m_name != "")
				AddClip(clip);

			xmlAnimation = xmlAnimation->NextSiblingElement("AnimationClip");
		}
	}

	void Animation::Render()
	{

	}

	void Animation::Update(float delta)
	{

	}

	void Animation::Stop(std::string clipName)
	{
		m_clips[clipName]->m_isPlaying = false;
	}

	void Animation::Rewind(std::string animation)
	{

	}

	bool Animation::IsPlaying(std::string animation)
	{
		return m_clips[animation]->m_isPlaying;
	}

	bool Animation::Play(std::string animation)
	{
		m_currentClip = m_clips.find(animation);
		m_currentClip->second->m_isPlaying = true;
		if (m_currentClip == m_clips.end())
		{
			std::cout << "Unable to play " << animation.c_str() << ". Animation not found" << std::endl;
			return false;
		}

		return true;
	}

	void Animation::AddClip(AnimationClip *const clip)
	{
		m_clips[clip->m_name] = clip;
	}

	void Animation::RemoveClip(std::string clipName)
	{
		auto iter = m_clips.find(clipName);
		if (iter == m_clips.end()) return;
		m_clips.erase(iter);
	}

	int Animation::GetClipCount()
	{
		return m_clips.size();
	}

	EMessageResult Animation::HandleMessage(const Message &msg)
	{
		TiXmlDocument xmlDoc;
		TiXmlElement *xmlElement;
		std::string str;

		switch (msg.m_type)
		{
		case MT_OBJECT_CREATED:
			str = std::string(static_cast<char *>(msg.m_data));
			if (xmlDoc.LoadFile(Singleton<Assets>::GetSingleton()->GetContentPath() + str) == false)
				std::cout << "LoadFile failed!: " << str << std::endl;
			xmlElement = xmlDoc.FirstChildElement("Animation");
			if (xmlElement)
			{
				Load(xmlElement);
			}
			return MR_TRUE;
		case MT_UPDATE:
			return MR_TRUE;
		}

		return MR_IGNORED;
	}
}
