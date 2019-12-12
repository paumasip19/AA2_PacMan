#include "Ranking.h"



Ranking::Ranking()
{
	returnButton = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("ReturnToMenuNormal", "Return", "", color(255, 0, 0)),
		Text("ReturnToMenuHover", "Return", "", color(0, 255, 0)),
		vec2(340, 600));

	for (int i = 0; i < 6; i++)
	{
		top.push_back({ "AAA", 0 });
	}

	std::ifstream findFile("../../res/files/ranking.bin", std::ios::in | std::ios::binary);
	if (findFile.fail())
	{
		std::ofstream newFile("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
		size_t len;

		for (int i = 0; i < 6; i++)
		{
			len = top[i].first.size();
			newFile.write(reinterpret_cast<char *>(&len), sizeof(size_t));
			newFile.write(top[i].first.c_str(), len);

			newFile.write(reinterpret_cast<char *>(&top[i].second), sizeof(top[i].second));
		}

		newFile.close();
	}

	findFile.close();

	readFile();
	saveFile();

	for (int i = 0; i < 5; i++)
	{
		std::string name = top[i].first;
		std::string text = (top[i].first) + " - " + std::to_string(top[i].second);
		rankOnScreen[i] = new Button(Font("PacFont", "../../res/ttf/Gameplay.ttf"),
			Text("Ranking" + std::to_string(i), top[i].first, "", color(0, 255, 0)),
			Text("Ranking" + std::to_string(i), top[i].first, "", color(0, 255, 0)),
			vec2(275, 150 + (i * 70)));
		punctuation[i] = new Button(Font("PacFont", "../../res/ttf/Gameplay.ttf"),
			Text("Punctuation" + std::to_string(i), std::to_string(top[i].second), "", color(0, 255, 0)),
			Text("Punctuation" + std::to_string(i), std::to_string(top[i].second), "", color(0, 255, 0)),
			vec2(575, 150 + (i * 70)));
	}
}

void Ranking::readFile()
{
	std::ifstream entrada("../../res/files/ranking.bin", std::ios::in | std::ios::binary);
	size_t len;
	for (int i = 0; i < 6; i++)
	{
		entrada.read(reinterpret_cast<char *>(&len), sizeof(size_t));
		char* temp = new char[len + 1];
		entrada.read(temp, len);

		temp[len] = '\0';
		top[i].first = temp;

		delete[]temp;

		entrada.read(reinterpret_cast<char *>(&top[i].second), sizeof(top[i].second));
	}

	//Order
	std::pair<std::string, int> temp;
	for (int i = 1; i < 6; ++i)
	{
		for (int j = 0; j < (6 - i); ++j)
			if (top[j].second < top[j + 1].second)
			{
				temp = top[j];
				top[j] = top[j + 1];
				top[j + 1] = temp;
			}
	}

	top.pop_back();

	entrada.close();
}

void Ranking::saveFile()
{
	std::ofstream salida("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
	size_t len;

	for (int i = 0; i < 5; i++)
	{
		len = top[i].first.size();
		salida.write(reinterpret_cast<char *>(&len), sizeof(size_t));
		salida.write(top[i].first.c_str(), len);

		salida.write(reinterpret_cast<char *>(&top[i].second), sizeof(top[i].second));
	}

	salida.close();
	salida.close();
}

void Ranking::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
	case IS_RUNNING:
		if (returnButton.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
		{
			sceneState = RETURN_TO_MENU;
		}
		break;
	case RETURN_TO_MENU:
		gameState = MENU;
		break;
	default:
		break;
	}
}

void Ranking::draw()
{
	returnButton.draw();
	for (int i = 0; i < 5; i++)
	{
		rankOnScreen[i]->draw();
		punctuation[i]->draw();
	}
}


Ranking::~Ranking()
{
}
