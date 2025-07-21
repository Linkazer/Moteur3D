#ifndef  TRANSFORM_H
#define TRANSFORM_H

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>

#pragma once
class Transform
{
public :
	explicit Transform();
	~Transform();

	/// <summary>
	/// Set the position of the GameObject.
	/// </summary>
	/// <param name="newPosition">The position where the GameObject will move to.</param>
	void SetPosition(glm::vec3 newPosition);
	/// <summary>
	/// Get the current position of the GameObject.
	/// </summary>
	/// <returns>The current position of the GameObject.</returns>
	glm::vec3 GetPosition() const;

	/// <summary>
	/// Make the Transform rotate around the X and Y axis.
	/// </summary>
	/// <param name="rotationWanted">The amount of degree to rotate.</param>
	void RotateByAngle(glm::vec2 rotationWanted);

	/// <summary>
	/// Rotate using Quaternions.
	/// </summary>
	/// <param name="rotationWanted">Rotation wanted.</param>
	void Rotate(glm::quat rotationWanted);

	/// <summary>
	/// Set the rotation of the Transform.
	/// </summary>
	/// <param name="rotationToSet">The Quaternion used to set the rotation.</param>
	void SetRotation(glm::quat rotationToSet);

	/// <summary>
	/// Get the current rotation of the Transform in Euler angles.
	/// </summary>
	/// <returns>The current rotation of the Transform.</returns>
	glm::vec3 GetEulerAngles() const;
	/// <summary>
	/// Get the current rotation of the Transform in Quaternion.
	/// </summary>
	/// <returns>The current rotation of the Transform.</returns>
	glm::quat GetQuaternion() const;

	/// <summary>
	/// Set the scale of the GameObject.
	/// </summary>
	/// <param name="scaleWanted">The new scale the GameObject will have.</param>
	void SetScale(glm::vec3 scaleWanted);
	/// <summary>
	/// Get the current scale of the GameObject.
	/// </summary>
	/// <returns>The current scale of the GameObject.</returns>
	glm::vec3 GetScale() const;

	/// <summary>
	/// Get the Model Matrix of the Transform.
	/// </summary>
	/// <returns>The Model Matrix of the Transform</returns>
	glm::mat4 GetModelMatrix();

	glm::vec3 GetForwardVector() const;
	glm::vec3 GetRightVector() const;
	glm::vec3 GetUpVector() const;

	glm::vec3 position; //REVIEW : See if we need it in public. (Only the Camera is using it)

private :
	glm::vec3 eulerAngles;
	glm::quat quaternion;
	glm::vec3 scale;

	glm::mat4 modelMatrix;
};
#endif
