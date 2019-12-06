#include "Play.h"

Play::Play()
{
	rectGame = { 0,0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT) };
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = { i * 35, j * 35, vec2(35,35) };
		}
	}
}

void Play::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
		case IS_RUNNING:
			break;
	}
}

void Play::draw()
{
}


Play::~Play()
{
}
