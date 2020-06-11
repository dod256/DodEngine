#include "GameLoop.h"
#include <vector>
#include <ctime> 
#include "..\Core\CallbackManager.h"
#include <functional>

void GameLoop::ProcessInput()
{
	if (GLFWwindow* window = DRenderManager.GetWindow())
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
}

void GameLoop::Terminate()
{
	DRenderManager.ShutDown();
}

void GameLoop::Update()
{
	ProcessInput();
	DRenderManager.PreUpdate();
	m_Field.Update();
	DRenderManager.PostUpdate();
}

bool GameLoop::IsStopped()
{
	return glfwWindowShouldClose(DRenderManager.GetWindow());
}

bool GameLoop::Init()
{
	srand(std::time(0));
	if (!DRenderManager.StartUp())
	{
		return 0;
	}
	m_Field.Init();
	return true;
}
