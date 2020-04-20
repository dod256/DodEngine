#include "CallbackManager.h"
#include "IClickable.h"

std::map<DU32, IClickable*> CallbackManager::m_MouseClickCallbacks;

void CallbackManager::RegisterCallback(DU32 ID, IClickable* object)
{
	std::pair<std::map<DU32, IClickable*>::iterator, bool> result;
	result = m_MouseClickCallbacks.insert(std::make_pair(ID, object));
	if (!result.second)
	{
		//ToDo
		//Already exist. What to do?
	}
}

void CallbackManager::UnregisterCallback(DU32 ID)
{
	m_MouseClickCallbacks.erase(ID);
}

void CallbackManager::OnClickInternal(float mouseXPos, float mouseYPos)
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

void CallbackManager::OnClick(GLFWwindow* window, int _button, int action, int mods)
{
	if (!action)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		OnClickInternal(x, y);
	}
}
