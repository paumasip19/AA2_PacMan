#pragma once
#include "Scene.h"
#include "Object.h"
#include "Button.h"

class Menu : public Scene
{
public:
	Object* background;

	Button playButton;
	Button rankingButton;
	Button exitButton;

	Menu();
	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void draw();
	~Menu();
};

