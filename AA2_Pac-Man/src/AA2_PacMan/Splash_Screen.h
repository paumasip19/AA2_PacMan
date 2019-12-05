#pragma once
#include <ctime> 
#include "Scene.h"
#include "Button.h"

class Splash_Screen : public Scene
{
public:

	Splash_Screen();

	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void draw();

	~Splash_Screen();
};

