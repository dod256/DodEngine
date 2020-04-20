#pragma once
#include <iostream>
#include "GameLoop.h"

int main()
{
	std::cout << "Hihi" << std::endl;
	GameLoop gameLoop;
	if (!gameLoop.Init())
	{
		return 0;
	}
	while (!gameLoop.IsStopped())
	{
		gameLoop.Update();
	}
	gameLoop.Terminate();

	return 0;
}
