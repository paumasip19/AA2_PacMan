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
	fullDeath = false;

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
	if (lifes != 0)
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
}

void Player::deathAnimation()
{
	if (lifes == 0)
	{
		timer = double(clock() - begin) / CLOCKS_PER_SEC;

		if (timer >= 0 && timer <= (TIME_DEATH_ANIM / 12) * 1)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 4,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 4,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 1 && timer <= (TIME_DEATH_ANIM / 12) * 2)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 5,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 4,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 2 && timer <= (TIME_DEATH_ANIM / 12) * 3)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 6,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 4,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 3 && timer < (TIME_DEATH_ANIM / 12) * 4)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 7,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 4,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 4 && timer < (TIME_DEATH_ANIM / 12) * 5)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 0,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 5 && timer < (TIME_DEATH_ANIM / 12) * 6)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 1,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 6 && timer < (TIME_DEATH_ANIM / 12) * 7)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 2,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 7 && timer < (TIME_DEATH_ANIM / 12) * 8)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 3,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 8 && timer < (TIME_DEATH_ANIM / 12) * 9)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 4,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 9 && timer < (TIME_DEATH_ANIM / 12) * 10)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 5,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 10 && timer < (TIME_DEATH_ANIM / 12) * 11)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 6,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 11 && timer < (TIME_DEATH_ANIM / 12) * 12)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 7,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 5,
				vec2(128, 128));
		}
		else if (timer >= (TIME_DEATH_ANIM / 12) * 12 && timer < (TIME_DEATH_ANIM / 12) * 13)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 3,
				(Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6,
				vec2(128, 128));
		}
		else if (timer >= TIME_DEATH_ANIM)
		{
			fullDeath = true;
		}
	}
}

void Player::draw()
{
	Renderer::Instance()->PushSprite("Atlas", rect, body);
}

Player::~Player()
{
}
