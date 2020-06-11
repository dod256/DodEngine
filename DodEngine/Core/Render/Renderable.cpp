#include "Renderable.h"

#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

//ToDo move to ResourceSystem
#define STB_IMAGE_IMPLEMENTATION
#include "..\External\stb_image.h"

Renderable::Renderable()
{
	m_Vertices.resize(0);
}

Renderable::~Renderable()
{
	glDeleteVertexArrays(1, &m_VertexArray);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_ElementBuffer);
}

Renderable::Renderable(const Renderable& object)
{
	m_Vertices = std::vector<DVertex>(object.m_Vertices);
	Init();
}

Renderable::Renderable(const std::vector<DVertex> vertices)
{
	m_Vertices = std::vector<DVertex>(vertices);
	Init();
}

Renderable& Renderable::operator = (const Renderable& object)
{
	if (m_IsInit)
	{
		glDeleteVertexArrays(1, &m_VertexArray);
		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteBuffers(1, &m_ElementBuffer);
	}
	m_Vertices = std::vector<DVertex>(object.m_Vertices);
	Init();
	return *this;
}

void Renderable::Draw() const
{
	if (!m_IsInit)
	{
		return;
	}
	if (m_IsWithTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
	glBindVertexArray(m_VertexArray);
	glDrawElements(GL_TRIANGLES, (int)m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Renderable::Init()
{
	if (m_IsInit)
	{
		glDeleteVertexArrays(1, &m_VertexArray);
		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteBuffers(1, &m_ElementBuffer);
	}
	m_IsInit = true;
	for (DU32 i = 1; i < m_Vertices.size() - 1; ++i)
	{
		m_Indices.push_back(0);
		m_Indices.push_back(i);
		m_Indices.push_back(i + 1);
	}

	glGenVertexArrays(1, &m_VertexArray);
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_ElementBuffer);
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(DVertex), &m_Vertices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), &m_Indices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//Init Texture

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderable::InitTexture(const char* fileName)
{
	m_IsWithTexture = true;
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Renderable::SetColor(Color color)
{
	for (DU32 i = 0; i < m_Vertices.size(); ++i)
	{
		m_Vertices[i].SetColor(DVec4(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
	}
	Init();
}