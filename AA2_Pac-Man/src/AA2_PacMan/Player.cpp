#include "Player.h"

Player::Player(Rect pos)
{
	//Carga de textura
	texture = new Text("Player", "", "../../res/img/PacManSpritesheet.png", color());
	Renderer* r = Renderer::Instance();
	r->LoadTexture(texture->id, texture->path);

	rect = Rect((r->GetTextureSize("Player").x / 8) * 6, 0, vec2(128, 128));

	lifes = 3;
	score = 0;
	speed = 1;

	lastDirec = InputKeys::LEFT;

	body = pos;
	lastPos = vec2(pos.x/35,pos.y/35);
}

vec2 Player::getPlayerPosition()
{
	return vec2(body.x, body.y);
}

vec2 Player::getPlayerSize()
{
	return vec2(body.w, body.h);
}

void Player::move()
{
	switch (lastDirec)
	{
		case InputKeys::UP:
			body.y -= speed;
			break;
		case InputKeys::DOWN:
			body.y += speed;
			break;
		case InputKeys::LEFT:
			body.x -= speed;
			break;
		case InputKeys::RIGHT:
			body.x += speed;
			break;
		default:
			break;
	}
}

bool Player::canMove()
{
	return false;
}

void Player::draw()
{
	Renderer::Instance()->PushSprite("Blue_Block", rect, body);
}

Player::~Player()
{
}
