#pragma once
#include "Button.h"
#include <string>
#include <iostream>


class HUD
{
public:
	Button points;
	Button fruitsPoints[3];
	Rect fruitsImages[3];
	Rect rectLifeOne;
	Rect rectLifeTwo;
	Rect rectLifeThree;

	HUD();

	void update(int p, int f1, int f2, int f3);
	void draw();

	~HUD();
};

