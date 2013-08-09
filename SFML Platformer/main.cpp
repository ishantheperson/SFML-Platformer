/* SFML Platformer Game
 * By Ishan Bhargava
 * Will probably not corrupt any memory (probably)
 * Please sign waiver before using
 */

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Game starting!" << std::endl;
	Game::Start();
	std::cout << "Game exiting!" << std::endl;
	return EXIT_SUCCESS;
}