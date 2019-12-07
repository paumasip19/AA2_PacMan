#pragma once
#include "Scene.h"
#include "Button.h"
#include "PowerUp.h"
#include "Player.h"
#include "HUD.h"
#include <ctime>

#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <fstream>
#include <sstream>

#include <stdlib.h>
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
	Button *pause;
	Button *sound;
	bool soundMusic;

	//Player
	Player *pacman;

	//Ranking new values
	std::string playerName;
	int score;
	int fruitsTimes[3];
	
	Play();
	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void readXML();
	void saveFile();
	void lifes();
	void startMesage();
	bool canMove();
	void draw();
	~Play();
};

