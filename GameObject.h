#pragma once

class GameObject : public Object
{
public:
	GameObject(Space *space, std::string name); //when parent object
	GameObject(GameObject *parent, std::string name); //when child object
	~GameObject();
	// disalbe copy and assign
	GameObject(const GameObject &rhs) = delete;
	void operator = (const GameObject &rhs) = delete;

	template<typename C>
	C *AddComponent();
	template<typename C>
	C *GetComponent();

	std::string &name() { return m_name; }
	GameObject &parent() const { return *m_parent; }

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update(float delta) override;
	virtual void Render() override;

	// 감시할 메세지를 등록
	template<typename C>
	void SubscribeToMessageType(EMessageType);
	// 특정 컴포넌트에 메세지를 보냄
	template<typename C>
	void PostMessage(const Message &);
	// 오브젝트의 모든 컴포넌트에 메세지를 보냄
	void BroadcastMessage(const Message &);
	bool Active() { return m_active; }
	void SetActive(bool active);
	void SetActiveRecursively(bool active);

private:
	GameObject *m_parent = nullptr;
	std::vector<GameObject *> m_children;
	std::unordered_map<std::type_index, Component *> m_components;
	std::set<Component *> m_subscriber[NUM_MESSAGE_TPYES];
	std::string m_name;
	Space *m_space;
	bool _initialized = false;
	bool _destroyed = false;
	bool m_active = false;
};

template<typename C>
C *GameObject::AddComponent()
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
C *GameObject::GetComponent()
{
	auto it = m_components.find(typeid(C));
	if (it == m_components.end()) return nullptr;
	return static_cast<C*>(it->second);
}

template<typename C>
void GameObject::SubscribeToMessageType(EMessageType msgType)
{
	auto ret = GetComponent<C>();
	assert(ret != nullptr);

	m_subscriber[msgType].insert(ret);
}

template<typename C>
void GameObject::PostMessage(const Message &msg)
{
	auto ret = GetComponent<C>();
	assert(ret != nullptr);

	for (auto compSet : m_subscriber[msg.m_type])
	{
		if (compSet == ret) {
			compSet->HandleMessage(msg);
		}
	}
}