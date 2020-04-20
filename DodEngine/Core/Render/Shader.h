#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const Shader& anotherShader);
	void Use();
	GLuint GetProgramID() { return ID; };
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec4(const std::string& name, float v1, float v2, float v3, float v4) const;
private:
	GLuint ID = 0;
};

