#pragma once

class GameInstance
{
public:
	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual bool IsExit() = 0;
	virtual void Terminate() = 0;
};

