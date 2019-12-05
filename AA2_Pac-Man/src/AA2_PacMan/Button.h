#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#undef main

#include "Constants.h"
#include "Renderer.h"
#include "Object.h"

#pragma once

class Button
{
private:
	Object object;

	Text *textureNormal;
	Text *textureHover;

public:
	Button();
	Button(Font font, Text normal, Text hover, vec2 pos);

	bool hover(vec2 &mouseCords, bool &click);
	void setTextureSize(vec2 size);
	void draw();
	
	~Button();
};

