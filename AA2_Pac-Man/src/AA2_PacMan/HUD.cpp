#include "HUD.h"

HUD::HUD()
{
	lifes = 3;

	points = Button(Font("PacFont", "../../res/ttf/Gameplay.ttf"),
		Text("Points", "0000", "", color(0, 0, 0)),
		Text("Points", "0000", "", color(0, 0, 0)),
		vec2(740, 50));

	fruitsPoints[0] = Button(Font("PacFont", "../../res/ttf/Gameplay.ttf"),
		Text("Fruit1", "X 0", "", color(0, 0, 0)),
		Text("Fruit1", "X 0", "", color(0, 0, 0)),
		vec2(770, 165));

	fruitsPoints[1] = Button(Font("PacFont", "../../res/ttf/Gameplay.ttf"),
		Text("Fruit2", "X 0", "", color(0, 0, 0)),
		Text("Fruit2", "X 0", "", color(0, 0, 0)),
		vec2(770, 235));

	fruitsPoints[2] = Button(Font("PacFont", "../../res/ttf/Gameplay.ttf"),
		Text("Fruit3", "X 0", "", color(0, 0, 0)),
		Text("Fruit3", "X 0", "", color(0, 0, 0)),
		vec2(770, 305));

	Renderer* r = Renderer::Instance();
	r->LoadTexture("Atlas", "../../res/img/PacManSpritesheet.png");

	fruitsImages[0] = Rect(0, (r->GetTextureSize("Atlas").x / 8) * 6, vec2(128, 128));
	fruitsImages[1] = Rect((r->GetTextureSize("Atlas").x / 8), (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	fruitsImages[2] = Rect((r->GetTextureSize("Atlas").x / 8) * 2, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));

	rectLifeOne = Rect((r->GetTextureSize("Atlas").x / 8) * 6, 0, vec2(128, 128));
	rectLifeTwo = Rect((r->GetTextureSize("Atlas").x / 8) * 6, 0, vec2(128, 128));
	rectLifeThree = Rect((r->GetTextureSize("Atlas").x / 8) * 6, 0, vec2(128, 128));
}

void HUD::update(int p, int f1, int f2, int f3, int l)
{
	lifes = l;

	if (p != std::stoi(points.textureNormal.text))
	{
		std::string pointStr = std::to_string(p);

		if (p == 0)  pointStr = "0000";
		else if (p < 10 && p != 0) pointStr = "000" + std::to_string(p);
		else if (p < 100 && p >= 10) pointStr = "00" + std::to_string(p);
		else if (p < 1000 && p >= 100) pointStr = "0" + std::to_string(p);

		updateText(pointStr, points);
	}
	


	if (f1 != fruitsPoints[0].textureNormal.text[2] - '0')
	{
		updateText("X " + std::to_string(f1), fruitsPoints[0]);
	}

	if (f2 != fruitsPoints[1].textureNormal.text[2] - '0')
	{
		updateText("X " + std::to_string(f2), fruitsPoints[1]);
	}

	if (f3 != fruitsPoints[2].textureNormal.text[2] - '0')
	{
		updateText("X " + std::to_string(f3), fruitsPoints[2]);
	}

}

void HUD::draw()
{
	points.draw();
	fruitsPoints[0].draw();
	fruitsPoints[1].draw();
	fruitsPoints[2].draw();

	Renderer* r = Renderer::Instance();
	r->PushSprite("Atlas", fruitsImages[0], Rect(700, 150, vec2(70, 70)));
	r->PushSprite("Atlas", fruitsImages[1], Rect(700, 220, vec2(70, 70)));
	r->PushSprite("Atlas", fruitsImages[2], Rect(700, 290, vec2(70, 70)));

	if (lifes > 0)
	{
		r->PushSprite("Atlas", rectLifeOne, Rect(695, 600, vec2(70, 70)));
		if (lifes > 1)
		{
			r->PushSprite("Atlas", rectLifeTwo, Rect(765, 600, vec2(70, 70)));
			if (lifes > 2)
			{
				r->PushSprite("Atlas", rectLifeThree, Rect(835, 600, vec2(70, 70)));
			}
		}
	}
}

void HUD::updateText(std::string t, Button &b)
{
	b = Button(b.f,
		Text(b.textureNormal.id, t, "", b.textureNormal.Color),
		Text(b.textureHover.id, t, "", b.textureNormal.Color),
		vec2(b.object->rect.x, b.object->rect.y));
}


HUD::~HUD()
{
}
