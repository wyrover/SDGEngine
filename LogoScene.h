#pragma once

namespace SDGEngine
{
	class LogoScene : public Scene
	{
	public:
		LogoScene();
		virtual ~LogoScene();

		virtual void Start() override;
		virtual void Finish() override;

		virtual void OnUpdate(float delta) override;
		virtual void OnRender() override;

	private:
		Entity *hero, *hero2;
		TileMap* m_Tilemap;
		Viewport* m_Viewport;
	};
}
