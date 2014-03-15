#pragma once

namespace sidescroll
{
	class GameScene;
	class SceneManager : public Object, public MySingleton<SceneManager>
	{
	public:
		SceneManager();
		~SceneManager();

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void Update(float delta) override;
		virtual void Render() override;

		void ChangeScene(GameScene* state);
		void PushScene(GameScene* state);
		void PopScene();

	private:
		std::vector<GameScene*> m_scene;
	};
}
