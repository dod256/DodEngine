#include "IClickable.h"
#include "InputManager.h"

DU32 IClickable::ID = 0;

IClickable::IClickable()
{
	m_ID = ID++;
	DInputManager.RegisterCallback(m_ID, this);
}

IClickable::IClickable(const IClickable& object)
{
	m_ID = ID++;
	DInputManager.RegisterCallback(m_ID, this);
}

IClickable::~IClickable()
{
	DInputManager.UnregisterCallback(m_ID);
}