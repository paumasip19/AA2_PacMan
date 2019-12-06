#pragma once
#include "Scene.h"
#include "Button.h"
#include "PowerUp.h"

#include <ctime>

#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <fstream>
#include <sstream>

#include <vector>

class Play : public Scene
{
public:

	//Map
	Rect rectGame;
	Rect map[20][20];

	//Init texts
	Button *pressSpace;
	Button *toStart;
	Text *black;
	Rect blackRect;

	//HUD
	Button *points;
	Button *fruits[3];
	Rect rectLifeOne;
	Rect rectLifeTwo;
	Rect rectLifeThree;

	//Paused
	Button *pause;
	Button *sound;
	bool soundMusic;

	//Ranking new values
	std::string playerName;
	int score;
	
	Play();
	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void readXML();
	void saveFile();
	void lifes();
	void startMesage();
	void updatePoints();
	void draw();
	~Play();
};

