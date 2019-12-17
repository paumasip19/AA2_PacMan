#pragma once
#include "Enemy.h"
class Inky : public Enemy
{
public:

	Inky();
	Inky(vec2);


	void Move();
	void animationSprite();
	void canDie();
	void die();
	void draw();

	~Inky();
};

