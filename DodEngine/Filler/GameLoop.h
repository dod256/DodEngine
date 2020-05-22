#pragma once
#include "..\Core\Constants.h"
#include "Field.h"
#include "..\Core\Player.h"
#include "..\Core\Render\Renderer.h"
#include "..\Core\Button.h"
#include "ColorSelection.h"

class ResetGameButton;

class GameLoop
{
public:
	GameLoop();
	~GameLoop();
	bool Init();
	void Update();
	bool IsStopped();
	void Terminate();
	void Reset();
private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void AddColorSelection(float x, float y, float a, float b, Color color);
	void ProcessInput();
	void UpdateInternal();
	Shader m_Shader;
	Shader m_TextShader;
	Shader m_DefaultShader;
	Shader m_TextureShader;
	Field m_Field;
	GLFWwindow* m_Window = nullptr;	
	std::vector<Player> m_Players;
	std::vector<ColorSelection> m_ColorSelections;
	Button m_Reset;
	bool m_GameEnded = false;
};

