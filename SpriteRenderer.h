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
		virtual EMessageResult HandleMessage(const Message &) override;

	private:
		Sprite *m_sprites = nullptr;
	};
}
