#pragma once

#include "..\Core\GameInstance.h"
#include "Field.h"

class AE : public GameInstance
{
public:
	virtual bool Init() override;
	virtual void Update() override;
	virtual bool IsExit() override { return m_bShouldExit; };
	virtual void Terminate() override;
private:
	bool m_bShouldExit;
	Field m_Field;
};

