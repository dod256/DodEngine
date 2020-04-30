#include "DPolygon.h"
#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "..\External\stb_image.h"

void DPolygon::Draw(const Shader& shader) const
{
	if (!m_NewWay)
	{
		m_OpenGLArea.Draw(shader);
		return;
	}
	//If Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glBindVertexArray(m_VertexArray);
	glDrawElements(GL_TRIANGLES, (int)m_Indices.size(), GL_UNSIGNED_INT, 0);
}

DPolygon::DPolygon(const std::vector<DVertex>& vertices)
{
	m_NewWay = true;
	m_Vertices = std::vector<DVertex>(vertices.begin(), vertices.end());
}

DPolygon::DPolygon(std::vector<DVec4> vertices, Color color)
{
	m_Color = color;
	m_VerticesOld = std::vector<DVec4>(vertices.begin(), vertices.end());
}

DPolygon::DPolygon(const DPolygon& anotherArea)
{
	m_Color = anotherArea.m_Color;
	m_VerticesOld = std::vector<DVec4>(anotherArea.m_VerticesOld.begin(), anotherArea.m_VerticesOld.end());
	m_Vertices = std::vector<DVertex>(anotherArea.m_Vertices.begin(), anotherArea.m_Vertices.end());
}

void DPolygon::Init()
{
	if(!m_NewWay)
	{
		std::vector<DU32> indices;
		for(DU32 i = 1; i < m_VerticesOld.size() - 1; ++i)
		{
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
		std::vector<Vertex> v;
		for(int i = 0; i < m_VerticesOld.size(); ++i)
		{
			std::pair<DFloat, DFloat> pair = Renderer::WorldToViewport(std::make_pair(m_VerticesOld[i][0], m_VerticesOld[i][1]));
			v.push_back(Vertex(pair.first, pair.second));
		}
		m_OpenGLArea = PrimitiveFigure(v, indices, m_Color);
		m_OpenGLArea.Init();
		return;
	}

	for(DU32 i = 1; i < m_Vertices.size() - 1; ++i)
	{
		m_Indices.push_back(0);
		m_Indices.push_back(i);
		m_Indices.push_back(i + 1);
	}

	/*
	for(const DVertex& vertex : m_Vertices)
	{
		DVertex viewportVertex;
		viewportVertex.SetColor(vertex.GetColor());
		viewportVertex.SetTexturePosition(vertex.GetTexturePosition());
		std::pair<DFloat, DFloat> viewportCoord = Renderer::WorldToViewport(std::make_pair(vertex.GetPosition()[0], vertex.GetPosition()[1]));
		DVec4 newCoord = vertex.GetPosition();
		newCoord[0] = viewportCoord.first;
		newCoord[1] = viewportCoord.second;
		viewportVertex.SetPosition(newCoord);
		m_ViewportVertices.push_back(viewportVertex);
	}
	*/

	m_Indices.push_back(0);
	m_Indices.push_back(1);
	m_Indices.push_back(3);
	m_Indices.push_back(1);
	m_Indices.push_back(2);
	m_Indices.push_back(3);

	for (const DVertex& vertex : m_Vertices)
	{
		std::pair<DFloat, DFloat> viewportCoord = Renderer::WorldToViewport(std::make_pair(vertex.GetPosition()[0], vertex.GetPosition()[1]));
		m_ViewportVertices.push_back(viewportCoord.first);
		m_ViewportVertices.push_back(viewportCoord.second);
		m_ViewportVertices.push_back(vertex.GetPosition()[2]);
		m_ViewportVertices.push_back(vertex.GetPosition()[3]);
		m_ViewportVertices.push_back(vertex.GetColor()[0]);
		m_ViewportVertices.push_back(vertex.GetColor()[1]);
		m_ViewportVertices.push_back(vertex.GetColor()[2]);
		m_ViewportVertices.push_back(vertex.GetColor()[3]);
		m_ViewportVertices.push_back(vertex.GetTexturePosition()[0]);
		m_ViewportVertices.push_back(vertex.GetTexturePosition()[1]);
	}

	glGenVertexArrays(1, &m_VertexArray);
	glGenBuffers(1, &m_VertexBuffer);
	glGenBuffers(1, &m_ElementBuffer);
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_ViewportVertices.size() * sizeof(DFloat), &m_ViewportVertices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), &m_Indices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//if Texture

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(2);

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
	unsigned char* data = stbi_load("kosh.jpeg", &width, &height, &nrChannels, 0);
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


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

DPolygon::~DPolygon()
{
	glDeleteVertexArrays(1, &m_VertexArray);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_ElementBuffer);
}

void DPolygon::SetColor(Color newValue)
{
	m_Color = newValue;
	m_OpenGLArea.SetColor(m_Color);
};