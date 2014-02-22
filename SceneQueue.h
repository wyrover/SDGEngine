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

		void addFromSceneQueue(GameScene *scene);
		void removeFromSceneQueue();
		void removeAllFromSceneQueue();
		void deleteAllFromRemovedQueue();
		size_t getSceneQueueSize();
		bool isEmpty();
		
	private:
		std::queue<GameScene *> m_SceneQueue;
		std::queue<GameScene *> m_RemovedSceneQueue;
	};
}
