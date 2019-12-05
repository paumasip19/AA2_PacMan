#include "Menu.h"

Menu::Menu()
{
	sceneState = IS_RUNNING;

	background = new Object(0, 0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT),
		"MenuBackground", "", "hola", color(0, 100, 0));

	Renderer::Instance()->LoadTexture(background->texture->id, background->texture->path);

}

void Menu::update()
{
	switch (sceneState)
	{
		case IS_RUNNING:
			break;
		case ENTER_RANKING:
			break;
		case ENTER_PLAY:
			break;
		default:
			break;
	}
}

void Menu::draw()
{
	Renderer::Instance()->PushImage(background->texture->id, background->rect);
}


Menu::~Menu()
{
}
