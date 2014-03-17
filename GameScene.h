#pragma once

namespace SDGEngine
{
	class GameScene : public Object
	{
	public:
		GameScene() {}
		virtual ~GameScene() {}

		bool isActive() { return m_active; }
		void setActive(bool active) { m_active = active; }

		virtual void Init() final;
		virtual void Destroy() final;
		virtual void Update(float delta) final;
		virtual void Render() final;

		virtual void Start() {}
		virtual void Finish() {}
		virtual void OnUpdate(float delta) { UNUSED(delta); }
		virtual void OnRender() {}

		void ChangeScene(GameScene* state);

	protected:
		Space *m_space = NULL;
		bool m_active = false;

	private:
		DISALLOW_COPY_AND_ASSIGN(GameScene);
	};
}
