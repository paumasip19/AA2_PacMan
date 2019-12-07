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
	int lastDirec;
	vec2 lastPos;

	clock_t begin;
	clock_t end;
	Rect body;

	Player(Rect pos);

	vec2 getPlayerPosition();
	vec2 getPlayerSize();
	void move();
	bool canMove();
	void draw();

	~Player();
};

