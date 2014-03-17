#pragma once

namespace SDGEngine
{
	class TitleScene : public GameScene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Start() override;
		virtual void Finish() override;

		virtual void OnUpdate(float delta) override;
		virtual void OnRender() override;

	private:

	};
}
