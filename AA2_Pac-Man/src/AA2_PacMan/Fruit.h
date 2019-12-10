#pragma once
#include "Object.h"
#include "Constants.h"
#include "Types.h"
#include <ctime>

class Fruit : public Object
{
public:
	FruitType type;
	int points;

	FruitType randOrder[(int)FruitType::COUNTSS];
	bool isVisible;
	bool firstTime;

	vec2 position;
	Rect body;

	clock_t begin;
	double timer;

	Fruit(Rect pos);
	void SetFruit();
	void SetConcreteFruit(int num);
	void collision(Rect pacMan, int &p, int &f1, int &f2, int &f3);
	void update(Rect pac, int &p, int &f1, int &f2, int &f3);
	void draw();
	~Fruit();
};

