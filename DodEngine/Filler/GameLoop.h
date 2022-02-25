#pragma once
#include "..\Core\Player.h"
#include "..\Core\GameInstance.h"
#include "..\Core\Render\Renderer.h"
#include "..\Core\Button.h"
#include "..\Core\Render\Renderable.h"

#include "..\Core\ResourceSystem.h"
#include "..\Core\Render\RenderManager.h"


#include "Filler_Field.h"
#include "..\Core\Menu.h"

class ResetGameButton;

class GameLoop : public GameInstance
{
public:
	virtual bool Init() override;
	virtual void Update() override;
	virtual bool IsExit()  override { return m_IsExit; };
	virtual void Terminate() override;
private:
	Filler_Field m_Field;
	Menu m_MainMenu;
	Menu m_Exit;
	bool m_IsInMenu = true;
	bool m_IsExit = false;
};

