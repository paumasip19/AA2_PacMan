#pragma once
#include "Object.h"
#include <ctime>

class Player : public Object
{
public:
private:

public:
	int lifes;
	int score;
	float speed;
	bool dead;
	bool fullDeath;
	int lastDirec;
	vec2 firstPos;
	vec2 lastPos;

	clock_t begin;
	double timer;

	Rect body;

	Player(Rect pos);

	vec2 getPlayerPosition();
	vec2 getPlayerSize();
	void move();
	void animationSprite();
	void deathAnimation();
	void draw();

	~Player();
};

