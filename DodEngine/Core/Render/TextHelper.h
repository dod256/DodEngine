#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <vector>
#include <string> 

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "Shader.h"

class TextHelper
{
public:
	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	static void Init();
	static void RenderText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
	static std::map<GLchar, Character> Characters;
	static GLuint VAO, VBO;

};

