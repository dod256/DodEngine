#include "GameLoop.h"
#include <vector>
#include <ctime> 
#include "..\Core\Render\TextHelper.h"
#include "..\Core\CallbackManager.h"
#include "ResetGameButton.h"

GameLoop::GameLoop()
{
	m_Players.reserve(2);
	m_ColorSelections.reserve(6);
}

void GameLoop::ProcessInput()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
}

void GameLoop::Terminate()
{
	glfwTerminate();
}

void GameLoop::UpdateInternal()
{
	ProcessInput();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const Player& player : m_Players)
	{
		if (m_Field.PlayerScore(player.GetID()) > 600)
		{
			std::string s = player.GetName() + " has won!";
			TextHelper::RenderText(m_TextShader, s, 600.0f, 560.0f, 0.4f, glm::vec3(1.0, 1.0f, 1.0f));
			m_GameEnded = true;
			for (ColorSelection& colorSelection : m_ColorSelections)
			{
				colorSelection.SetIsClickDisabled(true);
			}
			break;
		}
	}

	m_Shader.Use();
	m_Field.Draw(m_Shader);
	if (!m_GameEnded)
	{
		for (const ColorSelection& colorSelection : m_ColorSelections)
		{
			colorSelection.Draw(m_Shader);
		}
	}

	if (m_Reset)
	{
		m_Reset->Draw(m_Shader);
	}

	float y = 580.0f;
	for (const Player& player : m_Players)
	{
		std::string s = player.GetName() + ": " + std::to_string(m_Field.PlayerScore(player.GetID()));
		TextHelper::RenderText(m_TextShader, s, 20.0f, y, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));
		y -= 20.0f;		
	}

	TextHelper::RenderText(m_TextShader, "Reset", 480.0f, 565.0f, 0.3f, glm::vec3(1.0, 1.0f, 1.0f));

}

void GameLoop::Update()
{
	UpdateInternal();
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void GameLoop::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


bool GameLoop::IsStopped()
{
	return glfwWindowShouldClose(m_Window);
}

void GameLoop::CreateResetGameButton(float x, float y, float a, float b, Color color)
{
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(x - a, y - b));
	vertices.push_back(Vertex(x - a, y + b));
	vertices.push_back(Vertex(x + a, y + b));
	vertices.push_back(Vertex(x + a, y - b));
	std::vector<unsigned int> indices = {
	0, 1, 2,
	0, 2, 3
	};
	m_Reset = new ResetGameButton(vertices, indices, color, this);
	m_Reset->Init();
}

void GameLoop::AddColorSelection(float x, float y, float a, float b, Color color, Field* field)
{
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(x - a, y - b));
	vertices.push_back(Vertex(x - a, y + b));
	vertices.push_back(Vertex(x + a, y + b));
	vertices.push_back(Vertex(x + a, y - b));
	std::vector<unsigned int> indices = {
	0, 1, 2,
	0, 2, 3
	};
	m_ColorSelections.push_back(ColorSelection(vertices, indices, color, field));
	m_ColorSelections[m_ColorSelections.size() - 1].Init();
}

bool GameLoop::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT, "Filler", NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT);
	glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	srand(std::time(0));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	glfwSetMouseButtonCallback(m_Window, CallbackManager::OnClick);

	m_Shader = Shader("hex.vs", "hex.fs");
	Renderer::m_Window = m_Window;

	m_Field.Init();

	const std::vector<Color>& colors = m_Field.GetColors();

	for(DU32 i = 0; i < colors.size(); ++i)
	{
		AddColorSelection(-1.0f + 0.2f + i * 0.3f, -1.0f + 0.1f, 0.1f, 0.03f, colors[i], &m_Field);
	}

	Color resetColor(0.5f, 0.5f, 1.0f, 1.0f);
	CreateResetGameButton(0.0f, 0.9f, 0.1f, 0.03f, resetColor);

	// Set OpenGL options
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_TextShader = Shader("TextShader.vs", "TextShader.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(DEFAULT_WINDOWS_WIDTH), 0.0f, static_cast<GLfloat>(DEFAULT_WINDOWS_HEIGHT));
	m_TextShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(m_TextShader.GetProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	TextHelper::Init();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_Players.push_back(Player("Player1", false));
	m_Players.push_back(Player("AI"));

	return true;
}

GameLoop::~GameLoop()
{
	delete m_Reset;
}

void GameLoop::Reset()
{
	m_GameEnded = false;
	m_Field.Reset();
	for (ColorSelection& colorSelection : m_ColorSelections)
	{
		colorSelection.SetIsClickDisabled(false);
	}
}