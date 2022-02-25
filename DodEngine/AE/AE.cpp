#include "AE.h"
#include "../Core/Render/RenderManager.h"
#include "../Core/InputManager.h"

void AE::Terminate()
{
	DRenderManager.ShutDown();
}

void AE::Update()
{
	m_bShouldExit = glfwWindowShouldClose(DRenderManager.GetWindow());
	DInputManager.ProcessInput();
	DRenderManager.PreUpdate();

	m_Field.Update();

	DRenderManager.PostUpdate();
}

bool AE::Init()
{
	if (!DRenderManager.StartUp())
	{
		return 0;
	}
	m_Field.Init("AE_Assets/Maps/V.txt");
	return true;
}