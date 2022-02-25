#pragma once
#include "../precomp.h"
#include "DVertex.h"
#include "Color.h"
#include <vector>
#include <string>

class Renderable
{
public:
	Renderable();
	~Renderable();
	Renderable(const Renderable& object);
	//ToDo: change fileName to something better
	Renderable(const std::vector<DVertex> vertices, const char* fileName = 0);
	Renderable& operator = (const Renderable& object);
	void Draw() const;
	void SetColor(Color color);
	bool GetIsWithTexture() const { return m_IsWithTexture; };
private:
	void Init();
	void InitTexture();
	bool m_IsInit = false;
	//OpenGL Specific
	std::vector<DVertex> m_Vertices;
	std::vector<DU32> m_Indices;
	DU32 m_VertexArray = 0;
	DU32 m_VertexBuffer = 0;
	DU32 m_ElementBuffer = 0;
	//Texture
	std::string m_xFileName;
	bool m_IsWithTexture = false;
	DU32 m_Texture = 0;
};

