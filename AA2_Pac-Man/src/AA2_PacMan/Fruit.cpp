#include "Fruit.h"

//TODO
// NO ES PODEN REPETIR CADA 3 FRUITES DEL MATEIX TIPUS
//SUMAR HUD
Fruit::Fruit(Rect pos)
{
	Renderer* r = Renderer::Instance();
	r->LoadTexture("Atlas", "../../res/img/PacManSpritesheet.png");
	body = pos;
	SetFruit();
	isVisible = false;
	firstTime = true;

	begin = clock();
}

void Fruit::SetFruit()
{
	Renderer *r = Renderer::Instance();
	int rNum = rand() % 3;
	switch (rNum)
	{
		case 0:
			type = FruitType::CHERRY;
			points = 10;
			rect = Rect((r->GetTextureSize("Atlas").x / 8) * 0, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
			break;
		case 1:
			type = FruitType::STRAWBERRY;
			points = 15;
			rect = Rect((r->GetTextureSize("Atlas").x / 8) * 1, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
			break;
		case 2:
			type = FruitType::ORANGE;
			points = 20;
			rect = Rect((r->GetTextureSize("Atlas").x / 8) * 2, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
			break;
		default:
			break;
	}

	randOrder[2] = randOrder[1];
	randOrder[1] = randOrder[0];
	randOrder[0] = type;
}

void Fruit::SetConcreteFruit(int num)
{
	Renderer *r = Renderer::Instance();
	switch (num)
	{
	case 0:
		type = FruitType::CHERRY;
		points = 10;
		rect = Rect((r->GetTextureSize("Atlas").x / 8) * 0, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
		break;
	case 1:
		type = FruitType::STRAWBERRY;
		points = 15;
		rect = Rect((r->GetTextureSize("Atlas").x / 8) * 1, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
		break;
	case 2:
		type = FruitType::ORANGE;
		points = 20;
		rect = Rect((r->GetTextureSize("Atlas").x / 8) * 2, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
		break;
	default:
		break;
	}

	//if (randOrder[1] == type && randOrder[2] == type)

	randOrder[2] = randOrder[1];
	randOrder[1] = randOrder[0];
	randOrder[0] = type;

	
}

void Fruit::collision(Rect pacMan, int &p, int &f1, int &f2, int &f3)
{
	if (abs(pacMan.x - body.x) < 10 && abs(pacMan.y - body.y) < 10 && isVisible)
	{
		isVisible = false;
		p += points;
		
		begin = clock();
	}
}

void Fruit::update(Rect pac, int &p, int &f1, int &f2, int &f3)
{
	collision(pac, p, f1, f2, f3);

	timer = double(clock() - begin) / CLOCKS_PER_SEC;

	if (firstTime)
	{
		if (timer >= 10)
		{
			isVisible = true;
			firstTime = false;
		}
	}
	else
	{
		if (timer >= 15)
		{
			isVisible = true;
		}
	}
	
	std::cout << timer << std::endl;

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
