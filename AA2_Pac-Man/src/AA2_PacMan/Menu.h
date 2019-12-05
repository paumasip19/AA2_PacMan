#pragma once
#include "Scene.h"
#include "Object.h"
#include "Button.h"

class Menu : public Scene
{
public:
	Object* background;

	Menu();
	void update();
	void draw();
	~Menu();
};

