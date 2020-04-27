#pragma once
#include "..\precomp.h"
#include "..\Math\DVector.h"
class DVertex
{
public:
	DVertex() {};
	void SetPosition(DVec4 value) { m_Position = value; };
	DVec4 GetPosition() const { return m_Position; };
	void SetColor(DVec4 value) { m_Color = value; };
	DVec4 GetColor() const { return m_Color; };
	void SetTexturePosition(DVec2 value) { m_TexturePosition = value; };
	DVec2 GetTexturePosition() const { return m_TexturePosition; };
private:
	DVec4 m_Position;
	DVec4 m_Color;
	DVec2 m_TexturePosition;
};

