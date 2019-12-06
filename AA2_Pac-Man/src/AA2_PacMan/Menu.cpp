#include "Menu.h"

Menu::Menu()
{
	sceneState = IS_RUNNING;

	background = new Object(0, 0, vec2(900, 700),
		"MenuBackground", "", "../../res/img/PacManSpritesheet.png", color());

	Renderer::Instance()->LoadTexture(background->texture->id, background->texture->path);

	playButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonPlayNormal", "Play", "", color(255, 0, 0)),
		Text("ButtonPlayHover", "Play", "", color(0, 255, 0)),
		vec2(200, 100));

	rankingButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonRankingNormal", "Ranking", "", color(255, 0, 0)),
		Text("ButtonRankingHover", "Ranking", "", color(0, 255, 0)),
		vec2(200, 300));

	exitButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonExitNormal", "Exit", "", color(255, 0, 0)),
		Text("ButtonExitHover", "Exit", "", color(0, 255, 0)),
		vec2(200, 500));


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

			if (rankingButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
			{
				sceneState = ENTER_RANKING;
			}

			if (exitButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
			{
				sceneState = EXIT;
			}
			break;
		case ENTER_RANKING:
			gameState = RANKING;
			break;
		case ENTER_PLAY:
			gameState = PLAY;
			break;
		case EXIT:
			gameState = EXIT_GAME;
		default:
			break;
	}
}

void Menu::draw()
{
	Renderer::Instance()->PushImage(background->texture->id, background->rect);
	playButton.draw();
	rankingButton.draw();
	exitButton.draw();
}


Menu::~Menu()
{
}
