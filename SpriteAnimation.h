#pragma once

namespace SDGEngine
{
	enum EWrapMode
	{
		Once, // 한번만 플레이되고 마지막 모션에 고정된다.
		Loop, // 반복 플레이
		PingPong, // 한번 정방 재생되고 다시 역방으로 재생 루프
	};

	class AnimationClip
	{
	public:
		AnimationClip(std::string &name, int start, int end, float speed);

	private:
		bool isPlaying;
		std::string ClipName;
		int start;
		int end;
		float speed;
		int CurFrame;
		DISALLOW_COPY_AND_ASSIGN(AnimationClip);
		friend class SpriteAnimation;
	};

	class SpriteAnimation : public Sprite
	{
	public:
		SpriteAnimation() {}
		virtual ~SpriteAnimation();

		virtual void Update(float delta) override;
		virtual void Render() override;

		void Add(std::string &name, int start, int end, float speed);
		void Play(std::string &name);
		void Stop(std::string &name);
		AnimationClip *GetAni(std::string &name);

	private:
		std::list<AnimationClip *> m_clips;
		AnimationClip *CurrentAnim;
		int x = 0;
		int y = 0;
	};
}
