#include "SceneManager.h"

SceneManager SceneManager::m_SceneManager;
const int SceneManager::MAX_NUMBER_OF_SCENES = 16;

Scene* SceneManager::GetScene(DU32 sceneID)
{
	/*
	std::map<DU32, Scene*>::iterator it = m_Scenes.find(sceneID);
	if (it == m_Scenes.end())
	{
		return nullptr;
	}
	return it->second;
	*/
	return (0 <= sceneID && sceneID < MAX_NUMBER_OF_SCENES) ? m_Scenes[sceneID] : nullptr;
}

Scene* SceneManager::GetCurrentScene()
{
	return GetScene(m_CurrentScene);
}

DU32 SceneManager::GetNewSceneID()
{
/*
	DU32 res = SceneID::SceneID_Count;
	while (m_Scenes.find(res) != m_Scenes.end())
	{
		++res;
	}
	return res;
*/
	for (int i = SceneID::SceneID_Count; i < MAX_NUMBER_OF_SCENES; ++i)
	{
		if (m_Scenes[i] == nullptr)
		{
			return i;
		}
	}
	return MAX_NUMBER_OF_SCENES;
}

bool SceneManager::SetCurrentScene(DU32 sceneID)
{
	/*
	std::map<DU32, Scene*>::iterator it = m_Scenes.find(sceneID);
	if (it == m_Scenes.end())
	{
		return false;
	}
	m_CurrentScene = sceneID;
	return true;
	*/
	if (0 <= sceneID && sceneID < MAX_NUMBER_OF_SCENES && m_Scenes[sceneID])
	{
		m_CurrentScene = sceneID;
		return true;
	}
	return false;
}

bool SceneManager::AddScene(Scene* scene)
{
	if (!scene)
	{
		return false;
	}
	/*
	std::map<DU32, Scene*>::iterator it = m_Scenes.find(scene->GetID());
	if (it != m_Scenes.end())
	{
		return false;
	}
	m_Scenes.insert(std::make_pair(scene->GetID(), scene));
	return true;
	*/
	DU32 id = scene->GetID();
	if (0 <= id && id < MAX_NUMBER_OF_SCENES)
	{
		m_Scenes[id] = scene;
		return true;
	}
	return false;
}