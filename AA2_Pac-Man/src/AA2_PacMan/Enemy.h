#pragma once
#include "Object.h"
#include <ctime>

class Enemy : public Object
{
public:

	int points;
	char icon;
	vec2 initPos;
	
	int speed;
	bool dead;
	bool dotBehind;
	int lastDirec;
	vec2 lastPos;

	clock_t begin;
	double timer;

	Rect body;

	Enemy();
	Enemy(vec2);

	virtual void Move() = 0;
	virtual void animationSprite() = 0;
	virtual void draw() = 0;

	~Enemy();
};

