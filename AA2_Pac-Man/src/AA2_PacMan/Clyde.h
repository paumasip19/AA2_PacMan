#pragma once
#include "Enemy.h"
class Clyde : public Enemy
{
public:

	Clyde();
	Clyde(vec2);

	void Move();
	void animationSprite();
	void draw();

	~Clyde();
};

