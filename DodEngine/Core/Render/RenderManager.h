#pragma once
#include "Renderable.h"
#include "Shader.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string> 

#include <ft2build.h>
#include FT_FREETYPE_H  


#define DRenderManager RenderManager::GetRenderManager()

class RenderManager
{
public:
	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	static RenderManager& GetRenderManager() { return m_RenderManager; };
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void RenderText(std::string text, DFloat x, DFloat y, DFloat scale, DVec4 color);
	std::vector<DVertex> TextPolygon(std::string text, DFloat x, DFloat y, DFloat scale);
	RenderManager() {};
	~RenderManager() {};
	bool StartUp();
	void ShutDown();
	void PreUpdate();
	void PostUpdate();
	void Draw(const Renderable& renderable);
	void Draw(DU32 meshID);
	GLFWwindow* GetWindow() { return m_Window; };
private:
	static RenderManager m_RenderManager;
	Shader m_CameraShader;
	Shader m_TextShader;
	GLFWwindow* m_Window = nullptr;
	std::map<GLchar, Character> Characters;
	GLuint VAO = 0, VBO = 0;

};

