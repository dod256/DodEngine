#include "GameLoop.h"
#include <ctime> 
#include "..\Core\InputManager.h"
#include "..\Core\SceneManager.h"

void GameLoop::Terminate()
{
	DRenderManager.ShutDown();
}

void GameLoop::Update()
{
	m_IsExit = glfwWindowShouldClose(DRenderManager.GetWindow());
	DInputManager.ProcessInput();
	DRenderManager.PreUpdate();

	if (Scene* scene = DSceneManager.GetCurrentScene())
	{
		m_IsExit = m_IsExit || (scene->GetID() == SceneID::SceneID_Exit);
		if (m_IsExit)
		{
			return;
		}
		scene->Update();
	}
	
	DRenderManager.PostUpdate();
}

bool GameLoop::Init()
{
	if (!DRenderManager.StartUp())
	{
		return 0;
	}
	m_Field.Init();
	DSceneManager.AddScene(&m_Field);
	m_MainMenu = Menu(SceneID::SceneID_MainMenu);
	DSceneManager.AddScene(&m_MainMenu);
	m_Exit = Menu(SceneID::SceneID_Exit);
	DSceneManager.AddScene(&m_Exit);
	DSceneManager.SetCurrentScene(SceneID::SceneID_MainMenu);
	m_MainMenu.Init();
	return true;
}
