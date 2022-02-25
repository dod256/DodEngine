#pragma once
#include <map>
#include "Render\Renderer.h"
#include "precomp.h"

#define DInputManager InputManager::GetInputManager()

class IClickable;

class InputManager
{
public:
	static InputManager& GetInputManager() { return m_InputManager; };
	static void OnClick(GLFWwindow* window, int button, int action, int mods);
	void RegisterCallback(DU32 ID, IClickable* object);
	void UnregisterCallback(DU32 ID);
	void OnClickInternal(float mouseXPos, float mouseYPos);
	void ProcessInput();
private:
	static InputManager m_InputManager;
	std::map<DU32, IClickable*> m_MouseClickCallbacks;
};

