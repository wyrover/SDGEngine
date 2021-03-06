#include "Precompiled.h"

namespace SDGEngine
{
	void Space::Init()
	{
		if (_initialized)
			throw std::logic_error("The scene has already been initialized.");

		for (auto gameObject : m_gameObjects)
		{
			gameObject->Init();
		}
		_initialized = true;
	}

	void Space::Destroy()
	{
		if (_destroyed)
			throw std::logic_error("The scene has already been destroyed.");

		for (auto gameObject : m_gameObjects)
		{
			gameObject->Destroy();
			SDELETE(gameObject);
		}
		_destroyed = true;
	}

	void Space::Update(float delta)
	{
		for (auto gameObject : m_gameObjects)
		{
			if (m_requireSpriteSort)
			{
				std::sort(m_gameObjects.begin(), m_gameObjects.end(), Space::ZorderSort);
			}
			if (gameObject->Active())
				gameObject->Update(delta);
		}
	}

	void Space::Render()
	{
		for (auto gameObject : m_gameObjects)
		{
			if (gameObject->Active())
				gameObject->Render();
		}
	}

	void Space::Add(Entity *object)
	{
		if (object == NULL)
			throw std::invalid_argument("The object argument can't be null.");

		auto obj_it = std::find(m_gameObjects.begin(), m_gameObjects.end(), object);
		if (obj_it != m_gameObjects.end())
			throw std::logic_error("The object is already attached.");

		m_gameObjects.push_back(object);
	}

	void Space::Remove(Entity *object)
	{
		if (object == NULL)
			throw std::invalid_argument("The object argument can't be null.");

		auto obj_it = std::find(m_gameObjects.begin(), m_gameObjects.end(), object);
		if (obj_it == m_gameObjects.end())
			throw std::logic_error("The object is not attached.");

		m_gameObjects.erase(obj_it);
	}

	bool Space::ZorderSort(Entity *a, Entity *b)
	{
		auto sa = a->GetComponent<Sprite>();
		auto sb = b->GetComponent<Sprite>();
		if (sa && sb) {
			return Sprite::SpriteCompare(sa, sb);
		}
		return false;
	}
}
