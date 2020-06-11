#pragma once
#include "Constants.h"
#include "Player.h"
#include "Render\Renderer.h"
#include "Button.h"
#include "Render\Renderable.h"

#include "ResourceSystem.h"
#include "Render\RenderManager.h"


#include "..\Filler\Field.h"

class ResetGameButton;

class GameLoop
{
public:
	bool Init();
	void Update();
	bool IsStopped();
	void Terminate();
private:
	void ProcessInput();

	Field m_Field;
};

