#pragma once
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "..\Constants.h"
#include "IDrawable.h"

class Renderer
{
public:
	static std::pair<float, float> WindowCoordToViewportCoord(std::pair<float, float> originalCoordinates);
	//void Register(DU32 ID, IDrawable* object);
	//void Unregister(DU32 ID);
	//void Draw(DU32 ID);
public:
	static GLFWwindow* m_Window;
};

