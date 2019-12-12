#include "Button.h"
#include "Scene.h"
#include <string>
#pragma once

class Ranking : public Scene
{
public:
	
	Button returnButton;

	Button *rankOnScreen[5];
	Button *punctuation[5];
	std::vector<std::pair<std::string, int>> top;

	Ranking();

	void readFile();
	void saveFile();
	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void draw();

	~Ranking();
};

