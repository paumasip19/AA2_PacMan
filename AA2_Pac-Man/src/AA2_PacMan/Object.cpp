#include "Object.h"

Object::Object()
{
}

Object::Object(int rectX, int rectY, vec2 vecWH, std::string textureID, std::string textureText, std::string texturePath, color textureColor, bool isButton)
{
	texture = new Text(textureID, textureText, texturePath, textureColor);
	if(!isButton) Renderer::Instance()->LoadTexture(texture->id, texture->path);
	rect = Rect(rectX, rectY, Renderer::Instance()->GetTextureSize(texture->id));
}

Object::~Object()
{
}
