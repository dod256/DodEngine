#pragma once
#include "precomp.h"

class Scene
{
public:
	Scene();
	Scene(int sceneID);
	DU32 GetID() const { return m_SceneID; };
	virtual void Update() = 0;
private:
	DU32 m_SceneID = 0;
};

