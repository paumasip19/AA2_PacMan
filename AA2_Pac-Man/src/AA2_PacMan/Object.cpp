#include "Object.h"

Object::Object()
{
}

Object::Object(int rectX, int rectY, vec2 vecWH, std::string textureID, std::string textureText, std::string texturePath, color textureColor)
{
	texture = new Text(textureID, textureText, texturePath, textureColor);
	rect = Rect(rectX, rectY, Renderer::Instance()->GetTextureSize(texture->id));
}

Object::~Object()
{
}
