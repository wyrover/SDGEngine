#pragma once

namespace SDGEngine
{
	class Scene;
	class SceneSystem : public Object, public Singleton<SceneSystem>
	{
	public:
		SceneSystem();
		virtual ~SceneSystem();

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void Update(float delta) override;
		virtual void Render() override;

		void ChangeScene(Scene* state);
		void PushScene(Scene* state);
		void PopScene();

	private:
		std::vector<Scene*> m_scene;
		DISALLOW_COPY_AND_ASSIGN(SceneSystem);
	};
}
