#include "Precompiled.h"

namespace sidescroll
{
	GameObject::GameObject(Space *space, std::string name)
		:m_space(space), m_name(name)
	{
		if (space == nullptr)
			throw std::invalid_argument("space can't be nullptr.");

		m_space->Add(this);
	}

	GameObject::GameObject(GameObject *parent, std::string name)
		:m_parent(parent), m_name(name)
	{
		if (parent == nullptr)
			throw std::invalid_argument("parent can't be nullptr.");

		m_space = parent->m_space;
		parent->m_children.push_back(this);
	}

	GameObject::~GameObject()
	{
		if (!_destroyed)
		{
			Destroy();
		}
		for (auto pair : m_components)
		{
			delete pair.second;
		}
	}

	void GameObject::Init()
	{
		if (_initialized)
			throw std::logic_error("The game object has already been initialized.");

		for (auto pair : m_components)
		{
			pair.second->Init();
		}
		for (auto child : m_children)
		{
			child->Init();
		}
		_initialized = true;
	}

	void GameObject::Destroy()
	{
		if (_destroyed)
			throw std::logic_error("The game object has already been destroyed.");

		for (auto child : m_children)
		{
			child->Destroy();
		}
		for (auto pair : m_components)
		{
			pair.second->Destroy();
		}

		_destroyed = true;
	}

	void GameObject::Update(float delta)
	{
		for (auto pair : m_components)
		{
			pair.second->Update(delta);
		}
		for (auto child : m_children)
		{
			child->Update(delta);
		}
	}

	void GameObject::Render()
	{
		for (auto pair : m_components)
		{
			pair.second->Render();
		}
		for (auto child : m_children)
		{
			child->Render();
		}
	}

	void GameObject::BroadcastMessage(const Message &msg)
	{
		for (auto compSet : m_subscriber[msg.m_type])
		{
			compSet->HandleMessage(msg);
		}
	}

	void GameObject::SetActive(bool active)
	{
		m_active = active;
	}

	void GameObject::SetActiveRecursively(bool active)
	{
		// 부모가 없을때 까지
		if (m_parent != nullptr)
		{
			m_parent->SetActiveRecursively(active);
		}
		m_active = active;
		for (auto child : m_children)
		{
			child->SetActive(active);
		}
	}
}
