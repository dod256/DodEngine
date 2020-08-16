#pragma once
#include <map>

#include "precomp.h"
#include "Scene.h"

#define DSceneManager SceneManager::GetSceneManager()

enum SceneID
{
	SceneID_MainMenu = 0,
	SceneID_GameField = 1,
	SceneID_Rules = 2,
	SceneID_Exit = 3,
	SceneID_Count
};

class SceneManager
{
public:
	static const int MAX_NUMBER_OF_SCENES;
	static SceneManager& GetSceneManager() { return m_SceneManager; };
	Scene* GetCurrentScene();
	bool SetCurrentScene(DU32 sceneID);
	DU32 GetNewSceneID();
	bool AddScene(Scene* scene);
	Scene* GetScene(DU32 sceneID);
private:
	static SceneManager m_SceneManager;
	DU32 m_DefaultScene = 0;
	DU32 m_CurrentScene = 0;
	//std::map<DU32, Scene*> m_Scenes;
	Scene* m_Scenes[16];
};

