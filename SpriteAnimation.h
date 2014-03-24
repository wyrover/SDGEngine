#pragma once

namespace SDGEngine
{
	enum EWrapMode
	{
		Once, // �ѹ��� �÷��̵ǰ� ������ ��ǿ� �����ȴ�.
		Loop, // �ݺ� �÷���
		PingPong, // �ѹ� ���� ����ǰ� �ٽ� �������� ��� ����
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
