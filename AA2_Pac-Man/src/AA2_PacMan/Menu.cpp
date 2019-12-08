#include "Menu.h"

Menu::Menu()
{
	sceneState = IS_RUNNING;

	playButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonPlayNormal", "Play", "", color(255, 0, 0)),
		Text("ButtonPlayHover", "Play", "", color(0, 255, 0)),
		vec2(370, 150));

	rankingButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonRankingNormal", "Ranking", "", color(255, 0, 0)),
		Text("ButtonRankingHover", "Ranking", "", color(0, 255, 0)),
		vec2(325, 250));

	soundOnButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonSoundOnNormal", "Sound On", "", color(255, 0, 0)),
		Text("ButtonSoundOnHover", "Sound On", "", color(0, 255, 0)),
		vec2(310, 350));

	soundOffButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonSoundOffNormal", "Sound Off", "", color(255, 0, 0)),
		Text("ButtonSoundOffHover", "Sound Off", "", color(0, 255, 0)),
		vec2(290, 350));

	exitButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonExitNormal", "Exit", "", color(255, 0, 0)),
		Text("ButtonExitHover", "Exit", "", color(0, 255, 0)),
		vec2(380, 450));

	sound = Renderer::Instance()->isMusicOn();
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

			if (canClick)
			{
				if (sound)
				{
					if (soundOnButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
					{
						sound = false;
						Renderer::Instance()->pauseMusic();
						canClick = false;
					}
				}
				else
				{
					if (soundOffButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
					{
						sound = true;
						Renderer::Instance()->playMusic();
						canClick = false;
					}

				}
			}
			else if (!inputButtons[(int)InputKeys::MOUSE_LEFT]) canClick = true;
			
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
	Renderer::Instance()->SetRendreDrawColor(color(0,0,0));
	playButton.draw();
	rankingButton.draw();
	if(sound)soundOnButton.draw();
	else soundOffButton.draw();
	exitButton.draw();
}


Menu::~Menu()
{
}
