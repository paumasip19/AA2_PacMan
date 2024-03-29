#include "Fruit.h"

//TODO
//Si el player esta a la mateixa casella en el moment d'aparici�, esperar 2 segons
Fruit::Fruit(Rect pos)
{
	Renderer::Instance()->LoadTexture("Atlas", "../../res/img/PacManSpritesheet.png");
	body = pos;
	SetFruit();
	isVisible = false;
	firstTime = true;

	begin = clock();
	canAppear = true;
	canAppearAgain = true;
}

void Fruit::SetFruit()
{
	int rNum = rand() % 3;
	switch (rNum)
	{
		case 0:
			type = FruitType::CHERRY;
			points = 10;
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 0, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
			break;
		case 1:
			type = FruitType::STRAWBERRY;
			points = 15;
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 1, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
			break;
		case 2:
			type = FruitType::ORANGE;
			points = 20;
			rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 2, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
			break;
		default:
			break;
	}

	randOrder[2] = randOrder[1];
	randOrder[1] = randOrder[0];
	randOrder[0] = type;

	if (randOrder[1] == type && randOrder[2] == type)
	{
		int rNum2 = rNum;
		while (rNum == rNum2)
		{
			rNum = rand() % 3;
		}
		SetConcreteFruit(rNum);
	}
}

void Fruit::SetConcreteFruit(int num)
{
	switch (num)
	{
	case 0:
		type = FruitType::CHERRY;
		points = 10;
		rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 0, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
		break;
	case 1:
		type = FruitType::STRAWBERRY;
		points = 15;
		rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 1, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
		break;
	case 2:
		type = FruitType::ORANGE;
		points = 20;
		rect = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 2, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
		break;
	default:
		break;
	}

	randOrder[0] = type;
}

void Fruit::collision(Rect pacMan, int &p, int &f)
{
	if (abs(pacMan.x - body.x) < 10 && abs(pacMan.y - body.y) < 10 && isVisible)
	{
		isVisible = false;
		p += points;
		f++;
		begin = clock();
		canAppear = true;
		canAppearAgain = true;
	}
}

void Fruit::update(Rect pac, int &p, int &f1, int &f2, int &f3)
{
	switch (type)
	{
		case FruitType::CHERRY:
			collision(pac, p, f1);
			break;
		case FruitType::STRAWBERRY:
			collision(pac, p, f2);
			break;
		case FruitType::ORANGE:
			collision(pac, p, f3);
			break;
		default:
			break;
	}
	
	timer = double(clock() - begin) / CLOCKS_PER_SEC;

	if (canAppear)
	{
		if (firstTime)
		{
			if (timer >= 10)
			{
				if (abs(pac.x - body.x) < 10 && abs(pac.y - body.y) < 10 || canAppearAgain)
				{
					extraTimer = double(clock() - extraBegin) / CLOCKS_PER_SEC;

					if (extraTimer >= 2 && abs(pac.x - body.x) < 10 && abs(pac.y - body.y) < 10)
					{
						extraBegin = clock();
					}
					else if (extraTimer >= 2 && !abs(pac.x - body.x) < 10 && !abs(pac.y - body.y) < 10)
					{
						canAppearAgain = false;
						extraBegin = clock();
					}
				}
				else
				{
					SetFruit();
					isVisible = true;
					firstTime = false;
					begin = clock();
					canAppear = false;
					canAppearAgain = false;
				}
			}
		}
		else
		{
			if (timer >= 15)
			{
				if (abs(pac.x - body.x) < 10 && abs(pac.y - body.y) < 10 || canAppearAgain)
				{
					extraTimer = double(clock() - extraBegin) / CLOCKS_PER_SEC;

					if (extraTimer >= 2 && abs(pac.x - body.x) < 10 && abs(pac.y - body.y) < 10)
					{
						extraBegin = clock();
					}
					else if(extraTimer >= 2 && !abs(pac.x - body.x) < 10 && !abs(pac.y - body.y) < 10)
					{
						canAppearAgain = false;
						extraBegin = clock();
					}
				}
				else
				{
					SetFruit();
					isVisible = true;
					begin = clock();
					canAppear = false;
					canAppearAgain = false;
				}
			}
		}
	}
}

void Fruit::draw()
{
	if (isVisible)
	{
		Renderer::Instance()->PushSprite("Atlas", rect, body);
	}
}


Fruit::~Fruit()
{
}
