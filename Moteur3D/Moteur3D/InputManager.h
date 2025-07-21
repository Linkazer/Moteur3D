#ifndef  INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>
#include <map>
#include <vector>

#include "CPN_CameraController.h"

#include "Singleton.h"

#include "KeyAction.h"

#pragma once
class GLFWwindow;

class InputManager : public Singleton<InputManager>
{
public :
	explicit InputManager();
	virtual ~InputManager();

	/// <summary>
	/// Initialize Inputs handling.
	/// </summary>
	/// <param name="engineWindow">The window use by the Engine.</param>
	void Initialize(GLFWwindow* engineWindow);

	/// <summary>
	/// Update all inputs done this frame.
	/// </summary>
	void UpdateInputs();

	/// <summary>
	/// Get if a key is pressed or not.
	/// </summary>
	/// <param name="keyID">The ID of the key to check.</param>
	/// <returns>TRUE if the key is pressed. Otherwise, FALSE.</returns>
	bool GetKey(int keyID);
	/// <summary>
	/// Get if a mouse button is pressed or not.
	/// </summary>
	/// <param name="buttonID">The ID of the mouse button to check.</param>
	/// <returns>TRUE if the mouse button is pressed. Otherwise, FALSE.</returns>
	bool GetMouseButton(int buttonID);

	//--REVIEW : Try to use callbacks instead of checking every frame for inputs--
	void AddCallback(int key, int mod, int action, void(*callback)());
	void RemoveCallback(int key, int mod, int action, void(*callback)());
	//----------------------------------------------------------------------------

	/// <summary>
	/// Set the visibility of the mouse.
	/// </summary>
	/// <param name="shouldShow"></param>
	void ShowMouse(bool shouldShow);

	float mousePosX;
	float mousePosY;
	float lastMousePosX;
	float lastMousePosY;

private :
	GLFWwindow* window;

	bool isMouseShown;

	//--REVIEW : Try to use callbacks instead of checking every frame for inputs--
	std::map<KeyAction, std::vector<void(*)()>> keyCallbacksMap;

	static void ProcessKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	//----------------------------------------------------------------------------
};
#endif
