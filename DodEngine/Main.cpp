#pragma once
#include <iostream>
#include <string>
#include "Filler/GameLoop.h"
#include "AE/AE.h"

int main(int argc, const char* argv[])
{
	srand(std::time(0));
	std::cout << "Hihi" << std::endl;

	GameInstance* pxGame = nullptr;

	pxGame = new AE();

	// ToDo: move Filler to another project
	if (argc > 1)
	{
		std::string xGameName = argv[1];
		if (xGameName == "Filler")
		{
			delete pxGame;
			pxGame = new GameLoop();
		}
	}

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
