#include "Ball.h"



Ball::Ball(Text texture, vec2 pos)
{
	//Inicializar las texturas (ID, mensaje, path)
	pTexture = new Text(texture);

	Renderer* r = Renderer::Instance();
	r->LoadTexture(pTexture->id, pTexture->path);

	rect = { pos.x, pos.y, vec2(20, 20) };

	speed = 1;
	minusLife = false;
	changeDirPlat = false;
	changeDirBrick = false;
	direction = { speed, speed };
}

vec2 Ball::getBallPosition()
{
	return vec2(rect.x, rect.y);
}

void Ball::setBallMovement(char dir)
{
	if (dir == 'x') { rect.x += direction.x; }
	else if (dir == 'y') { rect.y += direction.y; }
}

void Ball::throwBall(bool spaceBar, vec2 playerPos, int &lastPlayerTouched)
{
	if (playerPos.x < SCREEN_WIDTH/2)
	{
		if(!spaceBar)
		{
			rect.x = playerPos.x + 70;
			rect.y = playerPos.y;
			lastPlayerTouched = 1;
		}
	}
	else
	{
		if (!spaceBar)
		{
			rect.x = playerPos.x - 27;
			rect.y = playerPos.y;
			lastPlayerTouched = 2;
		}
	}
}

void Ball::collisions(vec2 playerOnePos, vec2 playerTwoPos, vec2 playerOneSize, vec2 playerTwoSize, int &lifesOne, int &lifesTwo, int &lastPlayerTouched, int &pointsOne, int &pointsTwo)
{
	//Bordes Verticales (Porterias)
	if (rect.x < LEFT_BORDERB && minusLife == false) 
	{ 
		pointsOne -= 100;
		pointsTwo += 100;
		if (pointsOne < 0)
		{
			pointsOne = 0;
		}	
		minusLife = true;
		lifesOne--; 
	}
	else if (rect.x + rect.w > RIGHT_BORDERB && minusLife == false)
	{ 
		pointsOne += 100;
		pointsTwo -= 100;
		if (pointsTwo < 0)
		{
			pointsTwo = 0;
		}
		minusLife = true;
		lifesTwo--; 
	}

	//Bordes Horizontales
	if (rect.y + rect.h > DOWN_BORDERB || rect.y < UP_BORDERB) 
	{ 
		direction.y = -direction.y; 
	}

	//Jugadores
	if (rect.x > SCREEN_WIDTH / 2)
	{
		if ((rect.y >= playerTwoPos.y && rect.y <= playerTwoPos.y + playerTwoSize.y) || (rect.y + rect.h >= playerTwoPos.y && rect.y + rect.h <= playerTwoPos.y + playerTwoSize.y))
		{
			if (rect.x + rect.w >= playerTwoPos.x &&  rect.x + rect.w <= playerTwoPos.x + playerTwoSize.x && changeDirPlat == false)
			{
				lastPlayerTouched = 2;
				changeDirPlat = true;
				direction.x = -direction.x;
			}
		}
	}
	else
	{
		if ((rect.y >= playerOnePos.y && rect.y <= playerOnePos.y + playerOneSize.y) || (rect.y + rect.h >= playerOnePos.y && rect.y + rect.h <= playerOnePos.y + playerOneSize.y))
		{
			if (rect.x <= playerOnePos.x + playerOneSize.x && rect.x >= playerOnePos.x && changeDirPlat == false)
			{
				lastPlayerTouched = 1;
				changeDirPlat = true;
				direction.x = -direction.x;
			}
		}
	}

	if (rect.x > SCREEN_WIDTH / 4 && rect.x < SCREEN_WIDTH / 4 * 3) { changeDirPlat = false; }
	
}

bool Ball::brickCollision(vec2 brickPos, vec2 brickSize)
{
	if ((rect.y <= brickPos.y + brickSize.y && rect.x <= brickPos.x + brickSize.x && rect.y >= brickPos.y && rect.x >= brickPos.x) ||
		(rect.y <= brickPos.y + brickSize.y && rect.x + rect.w <= brickPos.x + brickSize.x && rect.y >= brickPos.y && rect.x + rect.w >= brickPos.x) ||
		(rect.y + rect.h <= brickPos.y + brickSize.y && rect.x <= brickPos.x + brickSize.x && rect.y + rect.h >= brickPos.y && rect.x >= brickPos.x) ||
		(rect.y + rect.h <= brickPos.y + brickSize.y && rect.x + rect.w <= brickPos.x + brickSize.x && rect.y + rect.h >= brickPos.y && rect.x + rect.w >= brickPos.x))
	{
		return true;
	}	
	else
	{
		return false;
	}
}


void Ball::draw()
{
	Renderer::Instance()->PushImage(pTexture->id, rect);
}

Ball::~Ball()
{
}
