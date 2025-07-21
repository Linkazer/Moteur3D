#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Transform.h"

Transform::Transform()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);

	quaternion = glm::quat(eulerAngles);
}

Transform::~Transform()
{
}

void Transform::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

glm::vec3 Transform::GetPosition() const
{
	return position;
}

void Transform::RotateByAngle(glm::vec2 rotationWanted) //REVIEW : See if we can add the Z axis.
{
	eulerAngles.x += rotationWanted.x;
	eulerAngles.y += rotationWanted.y;

	glm::quat rotationQuat = glm::angleAxis(glm::radians(eulerAngles.y), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationQuat *= glm::angleAxis(glm::radians(eulerAngles.x), glm::vec3(0.0f, 1.0f, 0.0f));

	SetRotation(rotationQuat);
}

void Transform::Rotate(glm::quat rotationWanted)
{
	SetRotation(quaternion * rotationWanted);
}

void Transform::SetRotation(glm::quat rotationToSet)
{
	quaternion = rotationToSet;
}

glm::vec3 Transform::GetEulerAngles() const
{
	return eulerAngles;
}

glm::quat Transform::GetQuaternion() const
{
	return quaternion;
}

void Transform::SetScale(glm::vec3 newScale)
{
	scale = newScale;
}

glm::vec3 Transform::GetScale() const
{
	return scale;
}

glm::mat4 Transform::GetModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotation = glm::mat4_cast(quaternion);
	glm::mat4 scalation = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = translation * rotation * scalation;

	return modelMatrix;
}

glm::vec3 Transform::GetForwardVector() const
{
	return glm::vec3(0.0f, 0.0f, -1.0f) * quaternion;
}

glm::vec3 Transform::GetRightVector() const
{
	return glm::vec3(1.0f, 0.0f, 0.0f) * quaternion;
}

glm::vec3 Transform::GetUpVector() const
{
	return glm::vec3(0.0f, 1.0f, 0.0f) * quaternion;
}
