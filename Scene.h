#pragma once

namespace SDGEngine
{
	class Scene : public Object
	{
	public:
		Scene() {}
		virtual ~Scene() {}

		bool isActive() { return m_active; }
		void setActive(bool active) { m_active = active; }
		void SetSpriteSort(bool b) { m_space->Sort(b); }
		Space *GetSpace() { return m_space; }

		virtual void Init() final;
		virtual void Destroy() final;
		virtual void Update(float delta) final;
		virtual void Render() final;

		virtual void Start() {}
		virtual void Finish() {}
		virtual void OnUpdate(float delta) { UNUSED(delta); }
		virtual void OnRender() {}

		void ChangeScene(Scene* state);

	private:
		Space *m_space = NULL;
		bool m_active = false;
		DISALLOW_COPY_AND_ASSIGN(Scene);
	};
}
