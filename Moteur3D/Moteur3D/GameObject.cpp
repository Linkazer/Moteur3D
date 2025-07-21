#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Engine.h"

GameObject::GameObject()
{
	transform = std::make_unique<Transform>();
}

GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	Engine::GetInstance()->InstantiateGameObject(*this);

	for (auto& component : components)
	{
		component->Initialize(*this);
	}
}

void GameObject::Start()
{
	for (auto& component : components)
	{
		component->Start();
	}
}

void GameObject::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component->Update(deltaTime);
	}
}

void GameObject::LateUpdate(float deltaTime)
{
	for (auto& component : components)
	{
		component->LateUpdate(deltaTime);
	}
}

void GameObject::Destroy()
{
	for (auto& component : components)
	{
		component->Destroy();
	}

	Engine::GetInstance()->DeleteGameObject(*this);
}

void GameObject::AddComponent(Component& componentToAdd)
{
	components.push_back(std::unique_ptr<Component>{ &componentToAdd });
	components.back()->Initialize(*this);
}

void GameObject::RemoveComponent(Component& componentToRemove)
{
	std::vector<std::unique_ptr<Component>>::iterator itComponent;

	for (itComponent = components.begin(); itComponent != components.end(); )
	{
		if (itComponent->get() == &componentToRemove)
		{
			itComponent->get()->Destroy();

			itComponent = components.erase(itComponent);
		}
		else
		{
			++itComponent;
		}
	}
}
