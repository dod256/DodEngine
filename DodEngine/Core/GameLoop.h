#pragma once
#include "Constants.h"
#include "Player.h"
#include "Render\Renderer.h"
#include "Button.h"
#include "Render\Renderable.h"

#include "ResourceSystem.h"
#include "Render\RenderManager.h"


#include "..\Filler\Field.h"
#include "Menu.h"

class ResetGameButton;

class GameLoop
{
public:
	bool Init();
	void Update();
	bool IsExit() { return m_IsExit; };
	void Terminate();
private:
	Field m_Field;
	Menu m_MainMenu;
	Menu m_Exit;
	bool m_IsInMenu = true;
	bool m_IsExit = false;
};

