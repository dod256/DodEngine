#include "Scene.h"
#include "SceneManager.h"

Scene::Scene()
{
	m_SceneID = DSceneManager.GetNewSceneID();
	DSceneManager.AddScene(this);
}

Scene::Scene(int sceneID)
{
	if (DSceneManager.GetScene(sceneID))
	{
		m_SceneID = DSceneManager.GetNewSceneID();
	}
	else
	{
		m_SceneID = sceneID;
	}
}