#pragma once
#include <iostream>
#include <string>
#include "AE/AE.h"

int main(int argc, const char* argv[])
{
	srand(std::time(0));
	std::cout << "Hihi" << std::endl;

	GameInstance* pxGame = nullptr;

	pxGame = new AE();

	if (!pxGame || !pxGame->Init())
	{
		return 0;
	}

	while (!pxGame->IsExit())
	{
		pxGame->Update();
	}

	pxGame->Terminate();
	delete pxGame;

	return 0;
}
