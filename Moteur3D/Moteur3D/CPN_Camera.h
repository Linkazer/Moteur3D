#ifndef  CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>

#include "Component.h"

#pragma once
class CPN_Camera : public Component
{
public :
	explicit CPN_Camera();
	virtual ~CPN_Camera();

	void Initialize(GameObject& nContainingGameObject) override;

	/// <summary>
	/// Get the View Matrix of the Camera.
	/// </summary>
	/// <returns>The View Matrix of the Camera.</returns>
	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix();

private :
	bool isPerspective = true;
};
#endif
