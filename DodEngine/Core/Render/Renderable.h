#pragma once
#include "../precomp.h"
#include "DVertex.h"
#include "Color.h"
#include <vector>

class Renderable
{
public:
	Renderable();
	~Renderable();
	Renderable(const Renderable& object);
	Renderable(const std::vector<DVertex> vertices);
	Renderable& operator = (const Renderable& object);
	void Draw() const;
	void SetColor(Color color);
private:
	void Init();
	void InitTexture(const char* fileName);
	bool m_IsInit = false;
	//OpenGL Specific
	std::vector<DVertex> m_Vertices;
	std::vector<DU32> m_Indices;
	DU32 m_VertexArray = 0;
	DU32 m_VertexBuffer = 0;
	DU32 m_ElementBuffer = 0;
	//Texture
	bool m_IsWithTexture = false;
	DU32 m_Texture = 0;

};

