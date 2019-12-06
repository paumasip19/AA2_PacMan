#include "Splash_Screen.h"


Splash_Screen::Splash_Screen()
{
	sceneState = IS_RUNNING;

	background = new Text("LoadScreen","","../../res/img/LoadScreen.png", color());
	Renderer* r = Renderer::Instance();
	r->LoadTexture(background->id, background->path);

	rectGame = { 0,0, vec2(SCREEN_WIDTH * 5, SCREEN_HEIGHT) };

	begin = clock();
}


void Splash_Screen::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
		case IS_RUNNING:
			timer = double(clock() - begin) / CLOCKS_PER_SEC;
			std::cout << timer << std::endl;

			if (timer >= 0.6 && timer <= 1.2)
			{
				rectGame.x = -SCREEN_WIDTH;
				break;
			}

			else if (timer >= 1.2 && timer <= 1.8)
			{
				rectGame.x = -SCREEN_WIDTH * 2;
				break;
			}

			else if (timer >= 1.8 && timer <= 2.4)
			{
				rectGame.x = -SCREEN_WIDTH * 3;
				break;
			}

			else if (timer >= 2.4 && timer < 3)
			{
				rectGame.x = -SCREEN_WIDTH * 4;
				break;
			}

			else if (timer >= 3)
			{
				sceneState = EXIT_TIME;
				break;
			}
			break;

		case EXIT_TIME:
			gameState = MENU;
			break;
	}
	
}

void Splash_Screen::draw()
{
	Renderer::Instance()->PushImage(background->id, rectGame);
}

Splash_Screen::~Splash_Screen()
{
}
