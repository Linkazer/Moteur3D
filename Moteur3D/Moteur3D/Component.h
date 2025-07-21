#ifndef  COMPONENT_H
#define COMPONENT_H

#pragma once
class GameObject;
class Transform;

class Component
{
public:
	explicit Component();
	virtual ~Component();

	/// <summary>
	/// Initialize the Component.
	/// </summary>
	/// <param name="nContainingGameObject">The GameObject containing the Component.</param>
	virtual void Initialize(GameObject& nContainingGameObject);
	/// <summary>
	/// Handle the Start logic of the Component.
	/// </summary>
	virtual void Start();
	/// <summary>
	/// Handle the Update logic of the Component.
	/// </summary>
	virtual void Update(float deltaTime);
	/// <summary>
	/// Handle the LateUpdate logic of the Component.
	/// </summary>
	virtual void LateUpdate(float deltaTime);
	
	/// <summary>
	/// Handle the Destroy logic of the Component.
	/// </summary>
	virtual void Destroy();

	/// <summary>
	/// Get the GameObject containing the Component.
	/// </summary>
	/// <returns>The GameObject containing the Component</returns>
	inline GameObject& GetGameObject() { return *containingGameObject; }

	/// <summary>
	/// Get the Transform used by the containingGameObject.
	/// </summary>
	/// <returns>The Transform used by the containingGameObject</returns>
	const Transform* GetTransform();

protected:
	/// <summary>
	/// Called when the Component is destroyed.
	/// </summary>
	virtual void OnDestroy();
	GameObject* containingGameObject;
};
#endif
