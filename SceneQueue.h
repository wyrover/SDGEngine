#pragma once

namespace sidescroll
{
	class SceneQueue : public Object
	{
	public:
		SceneQueue() {}
		virtual ~SceneQueue() {}

		virtual void Init() override;
		virtual void Destroy() override;
		virtual void Update(float delta) override;
		virtual void Render() override;

		void add(GameScene *scene);
		void remove();
		void removeAll();
		size_t getSize();
		bool isEmpty();
		
	private:
		std::queue<GameScene *> m_SceneQueue;
		static GameScene *m_current;
	};
}
