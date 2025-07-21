#include "GameObject.h"
#include "Transform.h"

#include "Component.h"


Component::Component()
{
	containingGameObject = nullptr;
}

Component::~Component()
{
}

void Component::Initialize(GameObject& nContainingGameObject)
{
	containingGameObject = &nContainingGameObject;
}

void Component::Start()
{
}

void Component::Update(float deltaTime)
{
}

void Component::LateUpdate(float deltaTime)
{
}

void Component::Destroy()
{
}

void Component::OnDestroy() 
{
}

const Transform* Component::GetTransform()
{
	return containingGameObject->GetTransform();
}