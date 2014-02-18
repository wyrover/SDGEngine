#pragma once

namespace sidescroll
{
	class AnimationClip : public Object
	{
	public:
		AnimationClip() :m_length(0.f), m_frameRate(0.f) {}
		virtual ~AnimationClip() {}

		virtual void Init() override {};
		virtual void Destroy() override {};
		virtual void Update(float delta) override {};
		virtual void Render() override {};

		float length() { return m_length; }
		float frameRate() { return m_frameRate; }
		bool IsPlaying() { return m_isPlaying; }

	private:
		float m_length;
		float m_frameRate;
		bool m_isPlaying = false;
		std::string m_name;
	};
}
