#include "CPN_CameraController.h"

#include <GLFW\glfw3.h>

#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"

//TEST
#include <iostream>

CPN_CameraController::CPN_CameraController()
	: Component()
{
}

CPN_CameraController::~CPN_CameraController()
{
}

void CPN_CameraController::Initialize(GameObject& nContainingGameObject)
{
	Component::Initialize(nContainingGameObject);

	/*InputManager::GetInstance()->AddCallback(GLFW_KEY_W, 0, GLFW_PRESS, InputEventMoveForward); //REVIEW : See if we can use callback instead of check on Update.
	InputManager::GetInstance()->AddCallback(GLFW_KEY_S, 0, GLFW_PRESS, InputEventMoveBackward);
	InputManager::GetInstance()->AddCallback(GLFW_KEY_A, 0, GLFW_PRESS, InputEventMoveRight);
	InputManager::GetInstance()->AddCallback(GLFW_KEY_D, 0, GLFW_PRESS, InputEventMoveLeft);

	InputManager::GetInstance()->AddCallback(GLFW_KEY_W, 0, GLFW_RELEASE, InputEventEndedMoveForward);
	InputManager::GetInstance()->AddCallback(GLFW_KEY_S, 0, GLFW_RELEASE, InputEventEndedMoveBackward);
	InputManager::GetInstance()->AddCallback(GLFW_KEY_A, 0, GLFW_RELEASE, InputEventEndedMoveRight);
	InputManager::GetInstance()->AddCallback(GLFW_KEY_D, 0, GLFW_RELEASE, InputEventEndedMoveLeft);*/
}



void CPN_CameraController::Update(float deltaTime)
{
	if (InputManager::GetInstance()->GetKey(GLFW_KEY_W))
	{
		containingGameObject->GetTransform()->position += movementSpeed * deltaTime * containingGameObject->GetTransform()->GetForwardVector();
	}
	else if (InputManager::GetInstance()->GetKey(GLFW_KEY_S))
	{
		containingGameObject->GetTransform()->position -= movementSpeed * deltaTime * containingGameObject->GetTransform()->GetForwardVector();
	}

	if (InputManager::GetInstance()->GetKey(GLFW_KEY_D))
	{
		containingGameObject->GetTransform()->position += movementSpeed * deltaTime * containingGameObject->GetTransform()->GetRightVector();
	}
	else if (InputManager::GetInstance()->GetKey(GLFW_KEY_A))
	{
		containingGameObject->GetTransform()->position -= movementSpeed * deltaTime * containingGameObject->GetTransform()->GetRightVector();
	}

	if (InputManager::GetInstance()->GetMouseButton(2))
	{
		InputManager::GetInstance()->ShowMouse(false);

		float xRotation = InputManager::GetInstance()->mousePosX - InputManager::GetInstance()->lastMousePosX;

		float yRotation = InputManager::GetInstance()->mousePosY - InputManager::GetInstance()->lastMousePosY;

		glm::vec2 rotationToApply = glm::vec2(xRotation, yRotation);

		containingGameObject->GetTransform()->RotateByAngle(rotationToApply * mouseSensibility * deltaTime);
	}
	else
	{
		InputManager::GetInstance()->ShowMouse(true);
	}
}

void CPN_CameraController::InputEventMoveForward()
{
	//cameraMovementDirection.x += 1;
}

void CPN_CameraController::InputEventMoveBackward()
{
	//cameraMovementDirection.x -= 1;
}

void CPN_CameraController::InputEventMoveRight()
{
	//cameraMovementDirection.y += 1;
}

void CPN_CameraController::InputEventMoveLeft()
{
	//cameraMovementDirection.y -= 1;
}

void CPN_CameraController::InputEventEndedMoveForward()
{
	//cameraMovementDirection.x -= 1;
}

void CPN_CameraController::InputEventEndedMoveBackward()
{
	//cameraMovementDirection.x += 1;
}

void CPN_CameraController::InputEventEndedMoveRight()
{
	//cameraMovementDirection.y -= 1;
}

void CPN_CameraController::InputEventEndedMoveLeft()
{
	//cameraMovementDirection.y += 1;
}
