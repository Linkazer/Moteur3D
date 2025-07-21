#include "CPN_Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"
#include "RenderingManager.h"

CPN_Camera::CPN_Camera()
	: Component()
{
}

CPN_Camera::~CPN_Camera()
{
}

void CPN_Camera::Initialize(GameObject& nContainingGameObject)
{
	Component::Initialize(nContainingGameObject);

	RenderingManager::GetInstance()->SetMainCamera(this);
}

glm::mat4 CPN_Camera::GetViewMatrix()
{
	glm::mat4 view;
	const Transform* tr = GetTransform();
	view = glm::lookAt(tr->GetPosition(), tr->GetPosition() + tr->GetForwardVector(), tr->GetUpVector());

	return view;
}

glm::mat4 CPN_Camera::GetProjectionMatrix()
{
	glm::mat4 projection;
	if (isPerspective)
	{
		projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f); //REVIEW : See where we can retrieve the window dimension.
	}
	else
	{
		projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f); //REVIEW : See where we can retrieve the window dimension.
	}

	return projection;
}
