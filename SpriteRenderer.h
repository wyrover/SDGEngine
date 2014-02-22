#pragma once

namespace sidescroll
{
	class SpriteRenderer : public Renderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void Update(float delta) override;
		virtual void Render() override;

	private:
		Sprite *m_sprites = nullptr;
		DWORD m_color;
	};
}
