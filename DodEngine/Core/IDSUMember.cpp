#include "IDSUMember.h"
#include <cassert>

std::vector<unsigned int> IDSUMember::m_Parent;

IDSUMember::IDSUMember()
{
	m_SetID = m_Parent.size();
	m_Parent.push_back(m_SetID);
}

IDSUMember::IDSUMember(const IDSUMember& anotherSet)
{
	m_SetID = anotherSet.m_SetID;
}

unsigned int IDSUMember::FindSet() const
{
	while (m_Parent[m_SetID] != m_SetID)
	{
		m_SetID = m_Parent[m_SetID];
	}
	return m_SetID;
}

void IDSUMember::UnionSets(IDSUMember* anotherSet) const
{
	unsigned int a = FindSet();
	unsigned int b = anotherSet->FindSet();
	if (a != b)
	{
		m_Parent[a] = b;
	}
}
