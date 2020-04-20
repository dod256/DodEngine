#include "Renderer.h"

GLFWwindow* Renderer::m_Window = nullptr;

std::pair<float, float> Renderer::WindowCoordToViewportCoord(std::pair<float, float> originalCoordinates)
{
	std::pair<float, float> result;
	int width, height;
	glfwGetWindowSize(m_Window, &width, &height);
	result.first = (2 * originalCoordinates.first - width) / (width);
	result.second = (height - 2 * originalCoordinates.second) / (height);
	return result;
}