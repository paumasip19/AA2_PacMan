#pragma once
#include "Object.h"
#include <ctime>

class Player : public Object
{
public:
private:
	Text * pTexture;
	Rect rectGame;
	Rect rectSprite;

public:
	int lifes;
	int score;
	float speed;

	bool isPowered;

	clock_t begin;
	clock_t end;

	Player(Text texture, vec2 posGame, vec2 posSprite);

	vec2 getPlayerPosition();
	vec2 getPlayerSize();
	void move();
	bool powerUpCollision();
	void draw();

	~Player();
};

