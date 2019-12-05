#include "Inputs.h"

Inputs::Inputs()
{
	mouseCoords = vec2(0,0);
	SetFalseKeyDown();
	SetFalseKeyPressed();
}

void Inputs::SetKeyValue(InputKeys key, bool value)
{
	if (!keyboardPressed[(int)key])
	{
		keyboardKeyDown[(int)key] = value;
	}
	else
	{
		keyboardKeyDown[(int)key] = false;
	}
	keyboardPressed[(int)key] = value;
}

void Inputs::SetFalseKeyDown()
{
	for (int i = 0; i < (int)InputKeys::COUNT; i++)
	{
		keyboardKeyDown[i] = false;
	}
}

void Inputs::SetFalseKeyPressed()
{
	for (int i = 0; i < (int)InputKeys::COUNT; i++)
	{
		keyboardPressed[i] = false;
	}
}

void Inputs::inputHandle(bool &isRunning)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) 
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					SetKeyValue(InputKeys::ESC, true);
					isRunning = false;
				}
				if (event.key.keysym.sym == SDLK_UP) SetKeyValue(InputKeys::UP, true);
				if (event.key.keysym.sym == SDLK_DOWN) SetKeyValue(InputKeys::DOWN, true);
				if (event.key.keysym.sym == SDLK_LEFT) SetKeyValue(InputKeys::LEFT, true);
				if (event.key.keysym.sym == SDLK_RIGHT) SetKeyValue(InputKeys::RIGHT, true);
				if (event.key.keysym.sym == SDLK_p) SetKeyValue(InputKeys::P, true);
				if (event.key.keysym.sym == SDLK_SPACE) SetKeyValue(InputKeys::SPACE, true);
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_ESCAPE) SetKeyValue(InputKeys::ESC, false);
				if (event.key.keysym.sym == SDLK_UP) SetKeyValue(InputKeys::UP, false);
				if (event.key.keysym.sym == SDLK_DOWN) SetKeyValue(InputKeys::DOWN, false);
				if (event.key.keysym.sym == SDLK_LEFT) SetKeyValue(InputKeys::LEFT, false);
				if (event.key.keysym.sym == SDLK_RIGHT) SetKeyValue(InputKeys::RIGHT, false);
				if (event.key.keysym.sym == SDLK_p) SetKeyValue(InputKeys::P, false);
				if (event.key.keysym.sym == SDLK_SPACE) SetKeyValue(InputKeys::SPACE, false);
				break;
			case SDL_MOUSEMOTION:
				mouseCoords.x = event.motion.x;
				mouseCoords.y = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, true);
				if (event.button.button == SDL_BUTTON_RIGHT) SetKeyValue(InputKeys::MOUSE_RIGHT, true);
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) SetKeyValue(InputKeys::MOUSE_LEFT, false);
				if (event.button.button == SDL_BUTTON_RIGHT) SetKeyValue(InputKeys::MOUSE_RIGHT, false);
				break;
			default:
				break;
		}
	}
}

Inputs::~Inputs()
{
}
