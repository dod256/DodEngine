#pragma once
#include "Constants.h"

class IClickable
{
public:
	IClickable();
	IClickable(const IClickable& object);
	~IClickable();
	virtual void OnClick(float mouseXPos, float mouseYPos) const = 0;
	bool GetIsClickDisabled() { return m_IsClickDisabled; };
	void SetIsClickDisabled(bool value) { m_IsClickDisabled = value; };
private:
	static DU32 ID;
	DU32 m_ID;
	bool m_IsClickDisabled = false;
};

