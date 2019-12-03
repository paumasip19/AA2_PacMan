#include "Button.h"
#include <iostream>
#include <string>

Button::Button()
{
}

Button::Button(Font font, Text normal, Text hover, vec2 pos)
{	
	//Inicializar las texturas (ID, mensaje, path)
	normalTexture = normal;
	hoverTexture = hover;
	
	Renderer* r = Renderer::Instance();
	r->LoadFont(font);
	r->LoadTextureText(font.id, normalTexture);
	r->LoadTextureText(font.id, hoverTexture);


	rect = { pos.x, pos.y, r->GetTextureSize(normalTexture.id) };
	
	texture = &normalTexture;
}

bool Button::hover(vec2 &mouseCords, bool &click)
{
	if (mouseCords.x > rect.x && mouseCords.x < (rect.x + rect.w) && mouseCords.y > rect.y && mouseCords.y < (rect.y + rect.h))
	{
		texture = &hoverTexture;
		if (click == true)
			return true;

	}
	else
	{
		texture = &normalTexture;
		return false;
	}
	return false;
}

void Button::setTextureSize(vec2 size)
{
	rect.w = size.x;
	rect.h = size.y;
}

void Button::draw()
{
	Renderer::Instance()->PushImage(texture->id, rect);
}

Button::~Button()
{
}
