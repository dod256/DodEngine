#pragma once
#include <iostream>
#include "Core\GameLoop.h"

int main()
{
	std::cout << "Hihi" << std::endl;
	GameLoop gameLoop;
	if (!gameLoop.Init())
	{
		return 0;
	}
	while (!gameLoop.IsExit())
	{
		gameLoop.Update();
	}
	gameLoop.Terminate();

	return 0;
}
