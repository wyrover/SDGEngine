#pragma once

namespace sidescroll
{
	class Animation : public Behaviour
	{
	public:
		Animation();
		virtual ~Animation();

		void Stop(std::string);
		void Rewind(std::string);
		bool IsPlaying(std::string);
		bool Play(std::string, EPlayMode mode = EPlayMode::StopSameLayer);
		void AddClip(AnimationClip *const clip, std::string newName);
		void RemoveClip(std::string clipName);
		int GetClipCount();

	private:
		std::map<std::string, AnimationClip*> m_clips;
		std::map<std::string, AnimationClip*>::iterator m_currentClip;
		bool m_playAutomatically = false;
		EWrapMode m_wrapMode;
	};
}
