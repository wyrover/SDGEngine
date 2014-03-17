#pragma once

namespace sidescroll
{
	class LogoScene : public GameScene
	{
	public:
		LogoScene();
		virtual ~LogoScene();

		virtual void Start() override;
		virtual void Finish() override;

		virtual void OnUpdate(float delta) override;
		virtual void OnRender() override;

	private:
		/*GameObject *hero = nullptr;*/
		TileMap* m_TileTempalte;
		Viewport* m_TileEngine;
	};
}
