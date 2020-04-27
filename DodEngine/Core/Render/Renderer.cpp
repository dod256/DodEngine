#include "Renderer.h"

GLFWwindow* Renderer::m_Window = nullptr;

std::pair<float, float> Renderer::MouseToViewport(std::pair<float, float> originalCoordinates)
{
	std::pair<float, float> result;
	int width, height;
	glfwGetWindowSize(m_Window, &width, &height);
	result.first = (2 * originalCoordinates.first - width) / (width);
	result.second = (height - 2 * originalCoordinates.second) / (height);
	return result;
}

std::pair<float, float> Renderer::WorldToViewport(std::pair<float, float> originalCoordinates)
{
	std::pair<float, float> result;
	int width, height;
	glfwGetWindowSize(m_Window, &width, &height);
	result.first = (2 * originalCoordinates.first - width) / (width);
	result.second = (2 * originalCoordinates.second - height) / (height);
	return result;
}

std::pair<float, float> Renderer::MouseToWorld(std::pair<float, float> originalCoordinates)
{
	std::pair<float, float> result;
	int width, height;
	glfwGetWindowSize(m_Window, &width, &height);
	result.first = originalCoordinates.first;
	result.second = height - originalCoordinates.second;
	return result;
}