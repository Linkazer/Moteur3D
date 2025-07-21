#include "InputManager.h"

#include <GLFW\glfw3.h>

void MousePositionCallback(GLFWwindow* window, double newMousePosX, double newMousePosY);

InputManager::InputManager()
	:Singleton<InputManager>()
{
	isMouseShown = true;
	keyCallbacksMap = std::map<KeyAction, std::vector<void(*)()>>();
}

InputManager::~InputManager()
{
}

void InputManager::Initialize(GLFWwindow* engineWindow)
{
	window = engineWindow;

	glfwSetCursorPosCallback(window, MousePositionCallback);

	//Key Input Handler
	glfwSetKeyCallback(window, ProcessKeyInput);
}

void InputManager::UpdateInputs()
{
	InputManager::GetInstance()->lastMousePosX = InputManager::GetInstance()->mousePosX;
	InputManager::GetInstance()->lastMousePosY = InputManager::GetInstance()->mousePosY;
}

bool InputManager::GetKey(int keyID)
{
	return glfwGetKey(window, keyID) == GLFW_PRESS;
}

bool InputManager::GetMouseButton(int buttonID)
{
	if (buttonID == 0)
	{
		return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	}
	else if (buttonID == 1)
	{
		return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
	}
	else if (buttonID == 2)
	{
		return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
	}

	return false;
}

void InputManager::AddCallback(int key, int mod, int action, void(*callback)())
{
	KeyAction keyAction = KeyAction(key, mod, action);

	if (keyCallbacksMap.find(keyAction) == keyCallbacksMap.end())
	{
		keyCallbacksMap.insert({ keyAction, std::vector<void(*)()>()});
	}

	keyCallbacksMap[keyAction].push_back(callback);
}

void InputManager::RemoveCallback(int key, int mod, int action, void(*callback)())
{
	KeyAction keyAction = KeyAction(key, mod, action);

	if (keyCallbacksMap.find(keyAction) != keyCallbacksMap.end())
	{
		keyCallbacksMap[keyAction].erase(std::remove(keyCallbacksMap[keyAction].begin(), keyCallbacksMap[keyAction].end(), callback), keyCallbacksMap[keyAction].end());

		if (keyCallbacksMap[keyAction].empty())
		{
			keyCallbacksMap.erase(keyAction);
		}
	}
}

void InputManager::ShowMouse(bool shouldShow)
{
	if (shouldShow != isMouseShown)
	{
		if (!shouldShow)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		isMouseShown = shouldShow;
	}
}

void InputManager::ProcessKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	KeyAction keyAction = KeyAction(key, mods, action);

	std::map<KeyAction, std::vector<void(*)()>> keyCallbacksMap = InputManager::GetInstance()->keyCallbacksMap;

	if (keyCallbacksMap.find(keyAction) != keyCallbacksMap.end())
	{
		for (void(*callback)() : keyCallbacksMap[keyAction])
		{
			std::invoke(callback);
		}
	}
}

void MousePositionCallback(GLFWwindow* window, double newMousePosX, double newMousePosY)
{
	InputManager::GetInstance()->mousePosX = newMousePosX;
	InputManager::GetInstance()->mousePosY = newMousePosY;
}
