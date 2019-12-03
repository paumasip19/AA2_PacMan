#include <iostream>
#include "GameController.h"

int main()
{
	srand(time(NULL));
	Renderer* r = Renderer::Instance();
	GameController *gameController = new GameController();
	
	while (gameController->isRunning)
	{
		r->Clear();
		gameController->gameLoop();
		r->Render();
	}

	return 0;
}