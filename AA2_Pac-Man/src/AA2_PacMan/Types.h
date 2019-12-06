#pragma once
#include <iostream>

enum GameState { SPLASH_SCREEN, MENU, RANKING, PLAY, EXIT_GAME };
enum SceneState { IS_RUNNING, EXIT_TIME, ENTER_RANKING, 
	ENTER_PLAY, RETURN_TO_MENU, START_GAME, PAUSED, 
	GAME_OVER, EXIT};

struct vec2
{
	int x;
	int y;

	vec2() { x = 0; y = 0; }
	vec2(int X, int Y) : x(X), y(Y) {}

	vec2 operator + (vec2 const &obj) {
		vec2 res;
		res.x = x + obj.x;
		res.y = y + obj.y;
		return res;
	}

	vec2 operator - (vec2 const &obj) {
		vec2 res;
		res.x = x - obj.x;
		res.y = y - obj.y;
		return res;
	}

	vec2 operator * (int const &obj)
	{
		vec2 res;
		res.x = x * obj;
		res.y = y * obj;
		return res;
	}

	vec2 operator / (int const &obj)
	{
		vec2 res;
		res.x = x / obj;
		res.y = y / obj;
		return res;
	}
};

struct Direction
{
	float x;
	float y;

	Direction() { x = 0; y = 0; }
	Direction(float X, float Y) : x(X), y(Y) {}
};

struct Font
{
	const std::string id;
	const int size = 40;
	const std::string path;

	Font() {}
	Font(std::string ID, std::string PATH) : id(ID), path(PATH) {}
};

struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a = 255;

	color() {}
	color(unsigned char R, unsigned char G, unsigned char B) : r(R), g(G), b(B) {}
};

struct Text
{
	std::string id;
	std::string text;
	std::string path;
	color Color;

	Text() {}
	Text(std::string ID, std::string TEXT, std::string PATH, color C) : id(ID), text(TEXT), path(PATH), Color(C) {}
	Text(const Text &t): id(t.id), text(t.text), path(t.path), Color(t.Color) {}
};

struct Rect
{
	int x;
	int y;
	int w;
	int h;

	Rect() {}
	Rect(int X, int Y, vec2 WH) : x(X), y(Y), w(WH.x), h(WH.y) {}
	Rect(vec2 XY, vec2 WH) : x(XY.x), y(XY.y), w(WH.x), h(WH.y) {}
};

enum InputKeys {NONE, ESC, SPACE, P, LEFT, RIGHT, UP, DOWN, 
	MOUSE_LEFT, MOUSE_RIGHT, COUNT};