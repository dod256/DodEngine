#pragma once
#include <vector>

class IDSUMember
{
public:
	unsigned int FindSet() const;
	void UnionSets(IDSUMember* anotherSet) const;
	IDSUMember();
	IDSUMember(const IDSUMember& anotherSet);
private:
	static std::vector<unsigned int> m_Parent;
	mutable unsigned int m_SetID;
};

