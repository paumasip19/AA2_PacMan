#include "Menu.h"

Menu::Menu()
{
	sceneState = IS_RUNNING;

	/*background = new Object(10, 0, vec2(500, 500),
		"MenuBackground", "", "../../res/img/PacManSpritesheet.png", color(0, 100, 0));

	Renderer::Instance()->LoadTexture(background->texture->id, background->texture->path);*/

	playButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonPlayNormal", "Play", "", color(255, 0, 0)),
		Text("ButtonPlayHover", "Play", "", color(0, 255, 0)),
		vec2(200, 100));


}

void Menu::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
		case IS_RUNNING:
			if (playButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
			{
				sceneState = ENTER_PLAY;
			}
			break;
		case ENTER_RANKING:
			gameState = RANKING;
			break;
		case ENTER_PLAY:
			gameState = PLAY;
			break;
		default:
			break;
	}
}

void Menu::draw()
{
	//Renderer::Instance()->PushImage(background->texture->id, background->rect);
	playButton.draw();
}


Menu::~Menu()
{
}
