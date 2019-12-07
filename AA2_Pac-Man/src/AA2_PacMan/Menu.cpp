#include "Menu.h"

Menu::Menu()
{
	sceneState = IS_RUNNING;

	playButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonPlayNormal", "Play", "", color(255, 0, 0)),
		Text("ButtonPlayHover", "Play", "", color(0, 255, 0)),
		vec2(200, 100));

	rankingButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonRankingNormal", "Ranking", "", color(255, 0, 0)),
		Text("ButtonRankingHover", "Ranking", "", color(0, 255, 0)),
		vec2(200, 150));

	soundOnButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonSoundOnNormal", "Sound On", "", color(255, 0, 0)),
		Text("ButtonSoundOnHover", "Sound On", "", color(0, 255, 0)),
		vec2(200, 200));

	soundOffButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonSoundOffNormal", "Sound Off", "", color(255, 0, 0)),
		Text("ButtonSoundOffHover", "Sound Off", "", color(0, 255, 0)),
		vec2(200, 200));

	exitButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ButtonExitNormal", "Exit", "", color(255, 0, 0)),
		Text("ButtonExitHover", "Exit", "", color(0, 255, 0)),
		vec2(200, 250));

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

			if (sound)
			{
				if (soundOnButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
				{
					sound = false;
					Renderer::Instance()->pauseMusic();
				}
			}
			else
			{
				if (soundOffButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT])) 
				{
					sound = true;
					Renderer::Instance()->playMusic();
				}
				
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
