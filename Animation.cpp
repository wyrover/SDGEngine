#include "Precompiled.h"

namespace sidescroll
{
	Animation::Animation()
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Stop(std::string clipName)
	{

	}

	void Animation::Rewind(std::string animation)
	{

	}

	bool Animation::IsPlaying(std::string animation)
	{
		return m_clips[animation]->IsPlaying();
	}

	bool Animation::Play(std::string animation, EPlayMode mode)
	{
		m_currentClip = m_clips.find(animation);
		if (m_currentClip == m_clips.end())
		{
			std::cout << "Unable to play " << animation.c_str() << ". Animation not found" << std::endl;
			return false;
		}

		return true;
	}

	void Animation::CrossFade(std::string animation, float fadeLength, EPlayMode mode)
	{

	}

	AnimationState *Animation::CrossFadeQueued(std::string animation, float fadeLength, EQueueMode queue, EPlayMode mode)
	{
		return nullptr;
	}

	AnimationState *Animation::PlayQueued(std::string animation, EQueueMode queue, EPlayMode mode)
	{
		return nullptr;
	}

	void Animation::AddClip(AnimationClip *const clip, std::string newName)
	{
		m_clips[newName] = clip;
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
