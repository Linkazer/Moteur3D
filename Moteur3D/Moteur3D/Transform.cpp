#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Transform.h"

Transform::Transform()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);

	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
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

void Transform::Rotate(glm::vec3 rotationWanted) //REVIEW : See if we can add the Z axis.
{
	glm::quat quatRotationWanted = glm::quat(rotationWanted * (3.14159f / 180.f));

	Rotate(quatRotationWanted);
}

void Transform::Rotate(glm::quat rotationWanted)
{
	rotation *= rotationWanted;
}

void Transform::SetRotation(glm::quat rotationToSet)
{
	rotation = rotationToSet;
}

void Transform::SetEulerAngles(glm::vec3 eulerAnglesToSet)
{
	rotation = glm::quat(eulerAnglesToSet * (3.14159f / 180.f));
}

glm::vec3 Transform::GetEulerAngles() const
{
	return glm::eulerAngles(rotation) * 3.14159f / 180.f;
}

glm::quat Transform::GetQuaternion() const
{
	return rotation;
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

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
	glm::mat4 scalationMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = translationMatrix * rotationMatrix * scalationMatrix;

	return modelMatrix;
}

glm::vec3 Transform::GetForwardVector() const
{
	return glm::vec3(0.0f, 0.0f, -1.0f) * rotation;
}

glm::vec3 Transform::GetRightVector() const
{
	return glm::vec3(1.0f, 0.0f, 0.0f) * rotation;
}

glm::vec3 Transform::GetUpVector() const
{
	return glm::vec3(0.0f, 1.0f, 0.0f) * rotation;
}
