#include "Brick.h"



Brick::Brick(Text texture, vec2 posGame, vec2 posSprite, char t, int l, int p)
{
	//Inicializar las texturas (ID, mensaje, path)
	pTexture = new Text(texture);

	Renderer* r = Renderer::Instance();

	rectGame = { posGame.x, posGame.y, r->GetTextureSize(pTexture->id) };
	rectSprite = { posSprite.x, posSprite.y, r->GetTextureSize(pTexture->id) };

	rectGame.w = rectSprite.w /= 5;
	rectGame.h = rectSprite.h /= 3;

	type = t;
	lifes = l;
	points = p;

	canHit = true;
}


bool Brick::collision()
{
	Renderer* r = Renderer::Instance();
	
	if (canHit) 
	{ 
		canHit = false;
		lifes--; 
	}
	
	switch (type)
	{
		case 'N':
			if (lifes == 0)
			{
				type = 'n';
				return true;
			}
			break;

		case 'H':
			if (lifes == 2)
			{
				rectSprite.x = (r->GetTextureSize("Bricks_Sprite").x / 5) * 2;
			}
			else if (lifes == 1)
			{

				rectSprite.x = (r->GetTextureSize("Bricks_Sprite").x / 5) * 4;
			}
			else if (lifes == 0)
			{
				type = 'n';
				return true;
			}
			
			break;

		case 'F':
			for (int i = 1; i < 4; i++)
			{
				rectSprite.x = (r->GetTextureSize("Bricks_Sprite").x / 5) * i;
			}
			rectSprite.x = 0;

			break;

		default:
			break;
	}
	return false;
}

void Brick::setSpritePos(vec2 pos)
{
	rectSprite.x = pos.x;
	rectSprite.y = pos.y;
}

vec2 Brick::getSpritePos()
{
	return vec2(rectGame.x, rectGame.y);
}

vec2 Brick::getSpriteSize()
{
	return vec2(rectGame.w, rectGame.h);
}

void Brick::draw()
{
	Renderer* r = Renderer::Instance();
	r->PushRotatedSprite(pTexture->id, rectSprite, rectGame, 90);
}

Brick::~Brick()
{
}
