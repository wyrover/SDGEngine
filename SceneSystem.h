#pragma once

namespace sidescroll
{
	class GameScene;
	class SceneSystem : public Object, public Singleton<SceneSystem>
	{
	public:
		SceneSystem();
		virtual ~SceneSystem();

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void Update(float delta) override;
		virtual void Render() override;

		void ChangeScene(GameScene* state);
		void PushScene(GameScene* state);
		void PopScene();

	private:
		std::vector<GameScene*> m_scene;
		DISALLOW_COPY_AND_ASSIGN(SceneSystem);
	};
}
