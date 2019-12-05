#include "Scene.h"
#include "Menu.h"
#include "Ranking.h"
#include "Splash_Screen.h"
#include "Play.h"
#include "Inputs.h"
#pragma once

class GameController
{
public:
	bool isRunning;
	GameState gameState;
	Inputs* inputs;
	Scene* scene;

	GameController();

	void gameLoop();

	~GameController();
};

