#pragma once

namespace sidescroll
{
	typedef void(*DeserializeFn)(File &file);
	class GameScene : public Object
	{
	public:
		GameScene() {}
		virtual ~GameScene() {}

		bool isActive() { return m_active; }
		bool isFinished() { return m_finished; }
		void setActive(bool active) { m_active = active; }
		void setFinished(bool finish) { m_finished = finish; }
		void setDeserialize(DeserializeFn fn = nullptr);
		void Deserialize(File &file);

		virtual void Init() final;
		virtual void Destroy() final;
		virtual void Update(float delta) final;
		virtual void Render() final;

		virtual void Start() {}
		virtual void Finish() {}
		virtual void OnUpdate(float delta) { UNUSED(delta); }
		virtual void OnRender() {}

	protected:
		Space *m_space;
		bool m_active = false;
		bool m_finished = false;
		DeserializeFn m_deserialize;
	};
}
