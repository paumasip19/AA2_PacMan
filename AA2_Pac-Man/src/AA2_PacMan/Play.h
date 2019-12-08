#pragma once
#include "Scene.h"
#include "Button.h"
#include "PowerUp.h"
#include "Player.h"
#include "HUD.h"
#include "Enemy.h"
#include "Inky.h"
#include "Clyde.h"
#include <ctime>

#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <fstream>
#include <sstream>

#include <stdlib.h>
#include <cstdlib>
#include <vector>

class Play : public Scene
{
public:

	//Map
	Rect rectGame;
	Rect map[20][20];
	char m[20][20];
	Text *atlas;
	Rect blue_block;
	Rect grey_block;
	Rect point_block;
	Rect powerUp_block;

	//Init texts
	Button pressSpace;
	Button toStart;	
	Rect black_block;

	//HUD
	HUD hud;
	
	//Paused
	Button PrSpace;
	Button ToResume;
	Button soundOn;
	Button soundOff;
	bool soundMusic;
	bool canClick;

	//Player
	Player *pacman;
	Inky *inkyF;
	Clyde *clydeF;

	//Ranking new values
	std::string playerName;
	int score;
	int fruitsTimes[3];
	int numDots;

	Play();
	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void readXML();
	void saveFile();
	void lifes();
	void startMesage();
	bool canEnemyMove(int);
	void playerKilled();
	bool canMove();
	void draw();
	~Play();
};

