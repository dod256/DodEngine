#include "InputManager.h"
#include "IClickable.h"
#include <iostream>
#include "Render\RenderManager.h"

InputManager InputManager::m_InputManager;

void InputManager::OnClick(GLFWwindow* window, int _button, int action, int mods)
{
	if (!action)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		std::cout << "Mouse click: " << x << " " << y << std::endl;
		DInputManager.OnClickInternal(x, y);
	}
}

void InputManager::RegisterCallback(DU32 ID, IClickable* object)
{
	std::pair<std::map<DU32, IClickable*>::iterator, bool> result;
	result = m_MouseClickCallbacks.insert(std::make_pair(ID, object));
	if (!result.second)
	{
		//ToDo
		//Already exist. What to do?
	}
}

void InputManager::UnregisterCallback(DU32 ID)
{
	m_MouseClickCallbacks.erase(ID);
}

void InputManager::OnClickInternal(float mouseXPos, float mouseYPos)
{
	for (std::pair<DU32, IClickable*> object : m_MouseClickCallbacks)
	{
		if (IClickable* clickable = object.second)
		{
			if (!clickable->GetIsClickDisabled())
			{
				clickable->OnClick(mouseXPos, mouseYPos);
			}
		}
	}
}

void InputManager::ProcessInput()
{
	if (GLFWwindow* window = DRenderManager.GetWindow())
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
}
