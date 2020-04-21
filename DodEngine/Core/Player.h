#pragma once
#include <string>

class Player
{
public:
	Player() { m_Name = "Random AI"; ID = NUMBER_OF_PLAYERS++; };
	Player(std::string name, bool isAI = true) : m_Name(name), m_IsAI(isAI) { ID = NUMBER_OF_PLAYERS++; };
	std::string GetName() const { return m_Name; };
	bool GetIsAI() const { return m_IsAI; };
	static unsigned int GetNumberOfPlayers() { return NUMBER_OF_PLAYERS; };
	unsigned int GetID() const { return ID; };
private:
	static unsigned int NUMBER_OF_PLAYERS;
	unsigned int ID = 0;
	std::string m_Name;
	bool m_IsAI = true;
};

