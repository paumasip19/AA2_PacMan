#include "GameController.h"

GameController::GameController()
{
	isRunning = true;
	scene = new Menu();
	inputs = new Inputs();
}

void GameController::gameLoop()
{
	inputs->inputHandle(isRunning);

	if (lastState != gameState)
	{
		switch (gameState)
		{
		case SPLASH_SCREEN:
			scene = new Splash_Screen();
			break;
		case MENU:
			scene = new Menu();
			break;
		case PLAY:
			scene = new Play();
			break;
		case RANKING:
			scene = new Ranking();
			break;
		default:
			break;

		}
	}
	
	lastState = gameState;

	scene->update();
	scene->draw();
}


GameController::~GameController()
{
}
