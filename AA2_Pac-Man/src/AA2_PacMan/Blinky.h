#pragma once
#include "Enemy.h"
class Blinky : public Enemy
{
public:
	
	Blinky();
	Blinky(vec2);


	void Move();
	void animationSprite();
	void canDie();
	void die();
	void draw();

	~Blinky();
};

