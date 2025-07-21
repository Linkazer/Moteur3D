#ifndef  ENGINE_H
#define ENGINE_H

#include <vector>
#include <memory>
#include "Singleton.h"

#pragma once
class GLFWwindow;
class RenderingManager;
class InputManager;
class GameObject;

/// <summary>
/// Handle the main part of the Engine.
/// </summary>
class Engine : public Singleton<Engine>
{
public:
	explicit Engine();
	virtual ~Engine();

	/// <summary>
	/// Initialize the Engine's data.
	/// </summary>
	/// <returns>TRUE if the Engine has been initialized. Otherwise, return FALSE.</returns>
	bool Initialize();
	/// <summary>
	/// Clean the Engine and everything that need to be cleanse link to it.
	/// </summary>
	void Clean();
	/// <summary>
	/// Ask to quit the Engine
	/// </summary>
	void Quit();

	/// <summary>
	/// Called at each frame. Handle the Update pass of the Engine.
	/// </summary>
	void Update(float deltaTime);
	/// <summary>
	/// Called after each Update. Handle the LateUpdate pass of the Engine.
	/// </summary>
	void LateUpdate(float deltaTime);
	/// <summary>
	/// Called after LateUpdate. Handle the render pass of the Engine.
	/// </summary>
	void Render();
	/// <summary>
	/// Called before the Update. Handle the Input Events pass of the Engine.
	/// </summary>
	void InputEvents();

	/// <summary>
	/// Check if the Engine is still running.
	/// </summary>
	/// <returns>TRUE if the Engine is still running. Otherwise, FALSE if the Engine should stop running.</returns>
	bool IsRunning();

	/// <summary>
	/// Instantiate a GameObject in the Engine, making it follow the Engine's routine (Update, LateUpdate, ...)
	/// </summary>
	/// <param name="toInstantiate">The GameObject to Instantiate.</param>
	void InstantiateGameObject(GameObject& toInstantiate);
	/// <summary>
	/// Remove a GameObject from the Engine. It can still exist if store somewhere else, but won't be used anymore.
	/// </summary>
	/// <param name="toDelete">The GameObject to remove from the Engine.</param>
	void DeleteGameObject(GameObject& toDelete);

private:
	GLFWwindow* window; //We can't use a smart pointer with GLFWwindow (TODO : Or we could create a custom deleter later)
	int widowWidth = 1280;
	int widowHeight = 720;

	std::unique_ptr<RenderingManager> renderingManagerPtr;
	std::unique_ptr<InputManager> inputManagerPtr;
	std::vector<GameObject*> instantiatedGameObjects;
};
#endif
