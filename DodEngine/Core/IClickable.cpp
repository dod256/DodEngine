#include "IClickable.h"
#include "CallbackManager.h"

DU32 IClickable::ID = 0;

IClickable::IClickable()
{
	m_ID = ID++;
	CallbackManager::RegisterCallback(m_ID, this);
}

IClickable::IClickable(const IClickable& object)
{
	m_ID = ID++;
	CallbackManager::RegisterCallback(m_ID, this);
}

IClickable::~IClickable()
{
	CallbackManager::UnregisterCallback(m_ID);
}