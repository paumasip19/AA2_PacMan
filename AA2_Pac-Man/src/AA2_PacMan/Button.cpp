#include "Button.h"
#include <iostream>
#include <string>

Button::Button()
{
}

Button::Button(Font font, Text normal, Text hover, vec2 pos)
{	
	textureNormal = normal;
	textureHover = hover;
	f = font;

	Renderer* r = Renderer::Instance();
	r->LoadFont(f);
	r->LoadTextureText(f.id, textureHover);
	r->LoadTextureText(f.id, textureNormal);

	object = new Object(pos.x, pos.y, vec2(100, 100),textureNormal.id, textureNormal.text, textureNormal.path, textureNormal.Color, true);
}

bool Button::hover(vec2 &mouseCords, bool &click)
{
	if (mouseCords.x > object->rect.x && mouseCords.x < (object->rect.x + object->rect.w) &&
		mouseCords.y > object->rect.y && mouseCords.y < (object->rect.y + object->rect.h))
	{
		object->texture = &textureHover;
		if (click == true)
			return true;
	}
	else
	{
		object->texture = &textureNormal;
		return false;
	}
	return false;
}

void Button::setTextureSize(vec2 size)
{
	object->rect.w = size.x;
	object->rect.h = size.y;
}

void Button::draw()
{
	Renderer::Instance()->PushImage(object->texture->id, object->rect);
}

Button::~Button()
{
}
