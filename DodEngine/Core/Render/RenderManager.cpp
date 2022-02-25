#include "RenderManager.h"
#include "..\ResourceSystem.h"
#include "..\InputManager.h"
#include <algorithm>

RenderManager RenderManager::m_RenderManager;

//ToDo: make it generic
const DFloat DEFAULT_WINDOWS_HEIGHT = 1000;
const DFloat DEFAULT_WINDOWS_WIDTH = 1200;

void RenderManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool RenderManager::StartUp()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(DEFAULT_WINDOWS_WIDTH, DEFAULT_WINDOWS_HEIGHT, "AE", NULL, NULL);
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

	glfwSetMouseButtonCallback(m_Window, InputManager::OnClick);
	m_CameraShader = Shader("Camera.vs", "Camera.fs");
	m_TextureShader = Shader("Texture.vs", "Texture.fs");

//-------------------------------------------------------------------------Text Init-------------------------------------------------------------------------------------------
	// Set OpenGL options
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_TextShader = Shader("TextShader.vs", "TextShader.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(DEFAULT_WINDOWS_WIDTH), 0.0f, static_cast<GLfloat>(DEFAULT_WINDOWS_HEIGHT));
	m_TextShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(m_TextShader.GetProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return true;
}

void RenderManager::PreUpdate()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void RenderManager::PostUpdate()
{
	glfwSwapBuffers(DRenderManager.GetWindow());
	glfwPollEvents();
}

void RenderManager::ShutDown()
{
	glfwTerminate();
}

void RenderManager::Draw(const Renderable& renderable)
{
	if (renderable.GetIsWithTexture())
	{
		m_TextureShader.Use();
		m_TextureShader.SetVec4("cameraPosition", DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f, DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f);
	}
	else
	{
		m_CameraShader.Use();
		m_CameraShader.SetVec4("cameraPosition", DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f, DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f);
	}
	renderable.Draw();
}

void RenderManager::Draw(DU32 meshID)
{
	if (Renderable* renderable = DResourceSystem.GetMesh(meshID))
	{
		if (renderable->GetIsWithTexture())
		{
			m_TextureShader.Use();
			m_TextureShader.SetVec4("cameraPosition", DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f, DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f);
		}
		else
		{
			m_CameraShader.Use();
			m_CameraShader.SetVec4("cameraPosition", DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f, DEFAULT_WINDOWS_WIDTH / 2.0f, DEFAULT_WINDOWS_HEIGHT / 2.0f);
		}
		renderable->Draw();
	}
}

std::vector<DVertex> RenderManager::TextPolygon(std::string text, DFloat x, DFloat y, DFloat scale)
{
	DFloat x1 = x;
	DFloat y1 = y;
	DFloat x2 = 0.0f;
	DFloat y2 = y;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		GLfloat h = ch.Size.y * scale;
		y2 = std::max(y2, ypos + h);
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	x2 = x;
	std::vector<DVertex> res(4);
	res[0].SetPosition(DVec4(x1, y1, 0.0f, 1.0f));
	res[1].SetPosition(DVec4(x1, y2, 0.0f, 1.0f));
	res[2].SetPosition(DVec4(x2, y2, 0.0f, 1.0f));
	res[3].SetPosition(DVec4(x2, y1, 0.0f, 1.0f));
	return res;
}

void RenderManager::RenderText(std::string text, DFloat x, DFloat y, DFloat scale, DVec4 color)
{
	// Activate corresponding render state	
	m_TextShader.Use();
	glUniform3f(glGetUniformLocation(m_TextShader.GetProgramID(), "textColor"), color[0], color[1], color[2]);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6)* scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}