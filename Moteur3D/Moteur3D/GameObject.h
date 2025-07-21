#ifndef  GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>

#pragma once
class Transform;
class Component;

class GameObject
{
public:
	explicit GameObject();
	~GameObject();
	
	/// <summary>
	/// Initialize the GameObject and its Components.
	/// </summary>
	void Initialize();
	/// <summary>
	/// Start the GameObject.
	/// </summary>
	void Start();
	/// <summary>
	/// Called at each Engine's Update. Update every Components.
	/// </summary>
	void Update(float deltaTime);
	/// <summary>
	/// Called at each Engine's LateUpdate. Update every Components.
	/// </summary>
	void LateUpdate(float deltaTime);
	/// <summary>
	/// Destroy the GameObject and its Components.
	/// </summary>
	void Destroy();

	/// <summary>
	/// Add a new Component to the GameObject.
	/// </summary>
	/// <param name="componentToAdd">The Component to add.</param>
	void AddComponent(Component& componentToAdd);
	/// <summary>
	/// Remove a Component from the GameObject.
	/// </summary>
	/// <param name="componentToRemove">The Component to remove.</param>
	void RemoveComponent(Component& componentToRemove);

	/// <summary>
	/// Get the first Component of the GameObject by its type.
	/// </summary>
	/// <typeparam name="T">The type of Component we want to get.</typeparam>
	/// <returns>The Component we wanted with the corresponding type.</returns>
	template<class T>
	T* GetComponentOfType();

	/// <summary>
	/// Get all Components of the GameObject of a specified type.
	/// </summary>
	/// <typeparam name="T">The type of Component we want to get.</typeparam>
	/// <returns>The vector of Components we found with the corresponding type.</returns>
	template<class T>
	std::vector<T*> GetAllComponentsOfType();

	/// <summary>
	/// Get the Transform of the GameObject.
	/// </summary>
	/// <returns>The Transform of the GameObject</returns>
	inline Transform* GetTransform() { return transform.get(); }

private:
	std::unique_ptr<Transform> transform;
	std::vector<std::unique_ptr<Component>> components;
};

template<class T>
T* GameObject::GetComponentOfType()
{
	std::vector<std::unique_ptr<Component>>::iterator itComponent;

	for (itComponent = components.begin(); itComponent != components.end(); )
	{
		if (typeid(*(itComponent->get())) == typeid(T))
		{
			return (T*)itComponent->get();
		}

		++itComponent;
	}

	return nullptr;
}

template<class T>
inline std::vector<T*> GameObject::GetAllComponentsOfType()
{
	std::vector<T*> toReturn = std::vector<T*>();

	std::vector<std::unique_ptr<Component>>::iterator itComponent;

	for (itComponent = components.begin(); itComponent != components.end(); )
	{
		if (typeid(*(itComponent->get())) == typeid(T))
		{
			toReturn.push_back((T*)itComponent->get());
		}

		++itComponent;
	}

	return toReturn;
}
#endif
