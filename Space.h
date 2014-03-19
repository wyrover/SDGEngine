#pragma once

namespace SDGEngine
{
	class Entity;
	class Space : public Object
	{
	public:
		Space() {}
		virtual ~Space() {}

		virtual void Init() override;
		virtual void Destroy() override;

		virtual void Update(float delta) override;
		virtual void Render() override;

		void Add(Entity *object);
		void Remove(Entity *object);
		void Sort(bool b) { m_requireSpriteSort = b; }

		static bool ZorderSort(Entity *a, Entity *b);

	private:
		std::vector<Entity *> m_gameObjects;
		bool m_requireSpriteSort = true;
		bool _initialized = false;
		bool _destroyed = false;
		DISALLOW_COPY_AND_ASSIGN(Space);
	};
}
