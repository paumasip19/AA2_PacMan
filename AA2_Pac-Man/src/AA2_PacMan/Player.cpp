#include "Player.h"

Player::Player(Rect pos)
{
	//Carga de textura
	Renderer* r = Renderer::Instance();
	r->LoadTexture("Atlas", "../../res/img/PacManSpritesheet.png");

	rect = Rect((r->GetTextureSize("Atlas").x / 8) * 6, 0, vec2(128, 128));


	lifes = 3;
	score = 0;
	speed = 1;

	dead = false;

	lastDirec = InputKeys::LEFT;

	body = pos;
	firstPos = vec2(pos.x/35, pos.y/35);
	lastPos = vec2(pos.x/35,pos.y/35);

	begin = clock();
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

void Player::animationSprite()
{
	timer = double(clock() - begin) / CLOCKS_PER_SEC;
	switch (lastDirec)
	{
		case InputKeys::UP:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 0, 0, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 1, 0, vec2(128, 128));
			}
			break;
		case InputKeys::DOWN:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 2, 0, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 3, 0, vec2(128, 128));
			}
			break;
		case InputKeys::LEFT:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 6, 0, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 7, 0, vec2(128, 128));
			}
			break;
		case InputKeys::RIGHT:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 4, 0, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 5, 0, vec2(128, 128));
			}
			break;
		default:
			break;
	}
}

void Player::draw()
{
	Renderer::Instance()->PushSprite("Atlas", rect, body);
}

Player::~Player()
{
}
