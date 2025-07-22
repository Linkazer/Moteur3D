#ifndef  CPN_CAMERACONTROLLER_H
#define CPN_CAMERACONTROLLER_H

#include <glm\glm.hpp>
#include "Component.h"

#pragma once
class CPN_CameraController : public Component
{
public :
	explicit CPN_CameraController();
	virtual ~CPN_CameraController();

	void Initialize(GameObject& nContainingGameObject) override;
	void Update(float deltaTime) override;

	//--REVIEW : Try to use callbacks instead of checking every frame for inputs--
	static void InputEventMoveForward();
	static void InputEventMoveBackward();
	static void InputEventMoveRight();
	static void InputEventMoveLeft();

	static void InputEventEndedMoveForward();
	static void InputEventEndedMoveBackward();
	static void InputEventEndedMoveRight();
	static void InputEventEndedMoveLeft();
	//----------------------------------------------------------------------------

private :
	float movementSpeed = 2.5f;
	float mouseSensibility = 5.0f;

	glm::vec2 cameraMovementDirection;

};
#endif
