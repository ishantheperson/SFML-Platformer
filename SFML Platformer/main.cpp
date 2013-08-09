// main.cpp : Defines the entry point for the application.

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Game starting!" << std::endl;
	Game::Start();
	std::cout << "Game exiting!" << std::endl;
	return EXIT_SUCCESS;
}