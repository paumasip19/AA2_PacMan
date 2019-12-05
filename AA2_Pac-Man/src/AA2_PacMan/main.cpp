#include <iostream>
#include "GameController.h"

int main()
{
	srand(time(NULL));
	//Renderer* r = Renderer::Instance();
	GameController *gameController = new GameController();
	
	while (gameController->isRunning)
	{
		gameController->gameLoop();
	}

	return 0;
}