#pragma once

namespace sidescroll
{
	class Animation : public Behaviour
	{
	public:
		Animation();
		virtual ~Animation();

		virtual void Init() override {};
		virtual void Destroy() override;
		virtual void Update(float delta) override;
		virtual void Render() override;
		virtual EMessageResult HandleMessage(const Message &) override;

		void AddClip(AnimationClip *const clip);
		bool Play(std::string);
		void Stop(std::string);
		void Rewind(std::string);
		bool IsPlaying(std::string);
		void RemoveClip(std::string clipName);
		int GetClipCount();

		void Save(TiXmlDocument *document);
		void Load(TiXmlElement *element);

	private:
		std::map<std::string, AnimationClip*> m_clips;
		std::map<std::string, AnimationClip*>::iterator m_currentClip;
		bool m_playAutomatically = true;
		std::string image;
		int width = 0;
		int height = 0;
		EWrapMode m_wrapMode = EWrapMode::Default;
	};
}
