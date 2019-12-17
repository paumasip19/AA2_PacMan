#include <iostream>
#include "GameController.h"

int main()
{
	srand(time(NULL));
	GameController *gameController = new GameController();
	
	while (gameController->isRunning)
	{
		Renderer::Instance()->Clear();
		gameController->gameLoop();
		Renderer::Instance()->Render();
	}

	return 0;
}