#pragma once
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "..\Core\Render\PrimitiveFigure.h"

class Button : public PrimitiveFigure
{
public:
	void OnClick(GLFWwindow* window, int button, int action, int mods) const;
	Button(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Color color) : PrimitiveFigure(vertices, indices, color) {};
	Button(const Button& button) : PrimitiveFigure(button) {};
protected:
	virtual void OnClickInternal() const = 0;
};

