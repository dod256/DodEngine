#pragma once
#include "Constants.h"
#include <map>
#include "Render\Renderer.h"

class IClickable;

class CallbackManager
{
public:
	static void RegisterCallback(DU32 ID, IClickable* object);
	static void UnregisterCallback(DU32 ID);
	static void OnClickInternal(float mouseXPos, float mouseYPos);
	static void OnClick(GLFWwindow* window, int button, int action, int mods);
private:
	static std::map<DU32, IClickable*> m_MouseClickCallbacks;
};

