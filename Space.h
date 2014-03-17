#pragma once

namespace SDGEngine
{
	class GameObject;
	class Space : public Object
	{
	public:
		Space() {}
		virtual ~Space() {}

		virtual void Init() override;
		virtual void Destroy() override;

		virtual void Update(float delta) override;
		virtual void Render() override;

		void Add(GameObject *object);
		void Remove(GameObject *object);

	private:
		std::vector<GameObject *> m_gameObjects;
		bool _initialized = false;
		bool _destroyed = false;
		DISALLOW_COPY_AND_ASSIGN(Space);
	};
}
