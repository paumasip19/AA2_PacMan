#pragma once
#include <ctime> 
#include "Scene.h"
#include "Button.h"

class Splash_Screen : public Scene
{
public:

	Splash_Screen();

	void update();
	void draw();

	~Splash_Screen();
};

