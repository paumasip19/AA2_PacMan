#include "Ranking.h"



Ranking::Ranking()
{
	returnButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ReturnToMenuNormal", "Return", "", color(255, 0, 0)),
		Text("ReturnToMenuHover", "Return", "", color(0, 255, 0)),
		vec2(340, 600));
}

void Ranking::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
	case IS_RUNNING:
		if (returnButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
		{
			sceneState = RETURN_TO_MENU;
		}
		break;
	case RETURN_TO_MENU:
		gameState = MENU;
		break;
	default:
		break;
	}
}

void Ranking::draw()
{
	returnButton.draw();
}


Ranking::~Ranking()
{
}
