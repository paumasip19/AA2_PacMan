#pragma once
#include "Types.h"
#include "Renderer.h"
//#include <iostream>

class Object
{
public:
	Rect rect;
	Text *texture;

	Object();
	Object(int rectX, int rectY, vec2 vecWH, 
		std::string textureID, std::string textureText, std::string texturePath, color textureColor, bool isButton);
	~Object();
};

