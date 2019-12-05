#include "Button.h"
#include "Scene.h"
#include <string>
#pragma once

class Ranking : public Scene
{
public:
	
	Ranking();

	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void draw();

	~Ranking();
};

