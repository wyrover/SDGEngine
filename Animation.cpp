#include "Precompiled.h"

namespace sidescroll
{
	Animation::Animation()
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Render()
	{

	}

	void Animation::Stop(std::string clipName)
	{
		m_clips[clipName]->isPlaying = false;
	}

	void Animation::Rewind(std::string animation)
	{

	}

	bool Animation::IsPlaying(std::string animation)
	{
		return m_clips[animation]->isPlaying;
	}

	bool Animation::Play(std::string animation)
	{
		m_currentClip = m_clips.find(animation);
		m_currentClip->second->isPlaying = true;
		if (m_currentClip == m_clips.end())
		{
			std::cout << "Unable to play " << animation.c_str() << ". Animation not found" << std::endl;
			return false;
		}

		return true;
	}

	void Animation::AddClip(AnimationClip *const clip)
	{
		m_clips[clip->name] = clip;
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
}
