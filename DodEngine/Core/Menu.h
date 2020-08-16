#pragma once
#include <vector>
#include "Button.h"
#include "..\Core\Render\Text.h"
#include "Scene.h"
#include "SceneManager.h"

class Menu : public Scene
{
public:
	Menu() : Scene() {};
	Menu(DU32 sceneID) : Scene(sceneID) {};
	~Menu();
	void Init();
	void Update() override;
private:
	void StartGame() { DSceneManager.SetCurrentScene(SceneID::SceneID_GameField); };
	void CloseGame() { DSceneManager.SetCurrentScene(SceneID::SceneID_Exit); };
	std::vector<IDrawable*> m_Items;
};

