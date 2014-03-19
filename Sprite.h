#pragma once

namespace SDGEngine
{
	class Sprite : public Component
	{
	public:
		Sprite();
		virtual ~Sprite() {}

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void Update(float delta) override;
		virtual void Render() override;
		virtual EMessageResult HandleMessage(const Message &) override;

		static inline bool SpriteCompare(const Sprite *a, const Sprite *b)
		{
			if (a->m_tx.zorder == b->m_tx.zorder)
				return a->m_texture < b->m_texture;
			else
				return a->m_tx.zorder < b->m_tx.zorder;
		}

	private:
		TextureAsset *m_texture = NULL;
		int width = 0, height = 0;
		D3DXVECTOR2 textureOffset = D3DXVECTOR2(0.f, 0.f);
		D3DXVECTOR2 textureScale = D3DXVECTOR2(0.f, 0.f);
		Transform m_tx;
		std::string name;
	};
}
