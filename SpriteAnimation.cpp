#include "Precompiled.h"

namespace SDGEngine
{
	AnimationClip::AnimationClip(std::string &name, int start, int end, float speed)
		: ClipName(name), start(start), end(end), speed(speed), CurFrame(start), isPlaying(false)
	{

	}

	SpriteAnimation::~SpriteAnimation()
	{
		for (auto i : m_clips) {
			SDELETE(i);
		}
	}

	void SpriteAnimation::Update(float delta)
	{
		if (CurrentAnim)
		{
			if (CurrentAnim->isPlaying)
			{
				CurrentAnim->CurFrame += CurrentAnim->speed * delta;
				if (CurrentAnim->CurFrame > CurrentAnim->end + 1) { CurrentAnim->CurFrame = CurrentAnim->start; }
			}

			x = (int)CurrentAnim->CurFrame % (int)(m_texture->width() / width);
			y = (int)CurrentAnim->CurFrame / (m_texture->width() / width);
		}
	}

	void SpriteAnimation::Render()
	{
		textureOffset = D3DXVECTOR2((x * width) / m_texture->width(), (y * height) / m_texture->height());
		textureScale = D3DXVECTOR2(width / m_texture->width(), height / m_texture->height());

		Sprite::Render();
	}

	void SpriteAnimation::Add(std::string &name, int start, int end, float speed)
	{
		AnimationClip *clip = new AnimationClip(name, start, end, speed);
		m_clips.push_back(clip);
	}

	void SpriteAnimation::Play(std::string &name)
	{
		CurrentAnim = GetAni(name);
		if (CurrentAnim) {
			CurrentAnim->isPlaying = true;
		}
	}

	void SpriteAnimation::Stop(std::string &name)
	{
		CurrentAnim = GetAni(name);
		if (CurrentAnim) {
			CurrentAnim->isPlaying = false;
		}
	}

	AnimationClip *SpriteAnimation::GetAni(std::string &name)
	{
		for (auto i : m_clips) {
			if (i->ClipName == name) {
				return i;
			}
		}

		std::cout << name << ": 애니메이션을 찾을 수 없습니다." << std::endl;
		return NULL;
	}
}