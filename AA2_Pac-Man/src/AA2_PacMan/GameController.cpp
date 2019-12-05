#include "GameController.h"

GameController::GameController()
{
	isRunning = true;
	scene = new Menu();
}

void GameController::gameLoop()
{
	scene->update();
	scene->draw();
}


GameController::~GameController()
{
}
