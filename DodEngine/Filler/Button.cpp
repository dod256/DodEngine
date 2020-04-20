#include "Button.h"
#include <algorithm>
#include <iostream>

void Button::OnClick(GLFWwindow* window, int button, int action, int mods) const
{
	if (action)
	{
		return;
	}
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	x = (2 * x - width) / (width);
	y = (height - 2 * y) / (height);
	std::vector<Vertex> vertices = GetVertices();
	std::cout << "Click: " << x << " " << y << " Button: " << vertices[0].GetX() << " " << vertices[0].GetY() << " " << vertices[2].GetX() << " " << vertices[2].GetY();
	if (vertices[0].GetX() <= x && x <= vertices[2].GetX() &&
		vertices[0].GetY() <= y && y <= vertices[2].GetY())
	{
		std::cout << " CLICK";
		OnClickInternal();
	}
	std::cout << std::endl;
}
