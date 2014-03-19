#pragma once

namespace SDGEngine 
{
	class Entity : public Object
	{
	public:
		Entity(Space *space, std::string name); //when parent object
		Entity(Entity *parent, std::string name); //when child object
		virtual ~Entity();

		template<typename C>
		C *AddComponent();
		template<typename C>
		C *GetComponent();
		template<typename C>
		bool RemoveComponent();
		bool RemoveComponent(Component *c);

		std::string &name() { return m_name; }
		Entity &parent() const { return *m_parent; }

		virtual void Init() override;
		virtual void Destroy() override;

		virtual void Update(float delta) override;
		virtual void Render() override;

		// 감시할 메세지를 등록
		template<typename C>
		void SubscribeToMessageType(EMessageType);
		// 모든 메세지 구독
		template<typename C>
		void SubscribeAllMessageType();
		// 특정 컴포넌트에 메세지를 보냄
		template<typename C>
		void PostMessage(const Message &);
		// 오브젝트의 모든 컴포넌트에 메세지를 보냄
		void BroadcastMessage(const Message &);
		bool Active() { return m_active; }
		void SetActive(bool active);
		void SetActiveRecursively(bool active);

	private:
		Entity *m_parent = NULL;
		std::vector<Entity *> m_children;
		std::unordered_map<std::type_index, Component *> m_components;
		std::set<Component *> m_subscriber[NUM_MESSAGE_TYPES];
		std::string m_name;
		Space *m_space;
		bool _initialized = false;
		bool _destroyed = false;
		bool m_active = false;
		DISALLOW_COPY_AND_ASSIGN(Entity);
	};

	template<typename C>
	C *Entity::AddComponent()
	{
		if (m_components.find(typeid(C)) != m_components.end())
		{
			std::string type_name = typeid(C).name();
			throw std::invalid_argument("component of type " + type_name + "is already attached");
		}

		C* component = new C();
		m_components[typeid(*component)] = component;
		component->m_gameObject = this;

		if (_initialized)
		{
			component->Init();
		}

		return component;
	}

	template<typename C>
	bool Entity::RemoveComponent()
	{
		auto it = m_components.find(typeid(C));
		if (it == m_components.end()) 
			return false;
		
		it->second->Destroy();
		SDELETE(it->second);
		m_components.erase(it);
		return true;
	}

	bool Entity::RemoveComponent(Component *c)
	{
		return RemoveComponent<decltype(c)>();
	}

	template<typename C>
	C *Entity::GetComponent()
	{
		auto it = m_components.find(typeid(C));
		if (it == m_components.end()) return NULL;
		return static_cast<C*>(it->second);
	}

	template<typename C>
	void Entity::SubscribeToMessageType(EMessageType msgType)
	{
		auto ret = GetComponent<C>();
		assert(ret != NULL);

		m_subscriber[msgType].insert(ret);
	}

	template<typename C>
	void Entity::SubscribeAllMessageType()
	{
		auto ret = GetComponent<C>();
		assert(ret != NULL);

		for (int i = 0; i < NUM_MESSAGE_TYPES; i++) {
			m_subscriber[i].insert(ret);
		}
	}

	template<typename C>
	void Entity::PostMessage(const Message &msg)
	{
		auto ret = GetComponent<C>();
		assert(ret != NULL);

		for (auto compSet : m_subscriber[msg.m_type])
		{
			if (compSet == ret) {
				compSet->HandleMessage(msg);
			}
		}
	}
}
