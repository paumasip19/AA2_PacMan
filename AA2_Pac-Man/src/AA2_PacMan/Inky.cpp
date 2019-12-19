#include "Inky.h"


Inky::Inky()
{

}

Inky::Inky(vec2 pos)
{
	Renderer::Instance()->LoadTexture("Atlas", "../../res/img/PacManSpritesheet.png");
	rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 6, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));

	points = 10;
	icon = 'F';
	initPos = pos;

	speed = 1;
	dead = false;
	dotBehind = true;
	isVulnerable = false;
	lastDirec = InputKeys::LEFT;
	newLastDirec = InputKeys::LEFT;
	lastPos = vec2(pos.x / 35, pos.y / 35);
	initPos = vec2(pos.x / 35, pos.y / 35);
	begin = clock();

	beginVulnerable = clock();
	vulnerableTimer = 0;

	beginDead = clock();
	deadTimer = 0;

	body = Rect(pos, vec2(35, 35));
}

void Inky::Move()
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

void Inky::animationSprite()
{
	timer = double(clock() - begin) / CLOCKS_PER_SEC;

	if (!isVulnerable)
	{
		switch (lastDirec)
		{
		case InputKeys::UP:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 0, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 1, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
			}
			break;
		case InputKeys::DOWN:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 2, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 3, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
			}
			break;
		case InputKeys::LEFT:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 6, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 7, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
			}
			break;
		case InputKeys::RIGHT:
			if (timer >= TIME_ANIM)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 4, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
				begin = clock();
			}
			else if (timer >= TIME_ANIM / 2)
			{
				rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 5, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 2, vec2(128, 128));
			}
			break;
		default:
			break;
		}
	}
}

void Inky::canDie()
{
	if (isVulnerable) vulnerableTimer = double(clock() - beginVulnerable) / CLOCKS_PER_SEC;

	if (vulnerableTimer >= VULNERABLE_TIME)
	{
		isVulnerable = false;
		beginVulnerable = clock();
	}

	if (isVulnerable)
	{
		if (timer >= TIME_ANIM)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 0, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 4, vec2(128, 128));
			begin = clock();
		}
		else if (timer >= TIME_ANIM / 2)
		{
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 2, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 4, vec2(128, 128));
		}
	}
}

void Inky::die()
{
	if (dead)
	{
		deadTimer = double(clock() - beginDead) / CLOCKS_PER_SEC;
		if (deadTimer >= DEAD_TIME)
		{
			dead = false;
			isVulnerable = false;
			body.x = initPos.x * 35;
			body.y = initPos.y * 35;
			beginDead = clock();
		}
	}
	std::cout << deadTimer << std::endl;
}

void Inky::draw()
{
	Renderer::Instance()->PushSprite("Atlas", rect, body);
}


Inky::~Inky()
{
}
