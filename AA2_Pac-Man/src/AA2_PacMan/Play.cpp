#include "Play.h"

Play::Play()
{
	sceneState = START_GAME;
	rectGame = { 0,0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT) };
	readXML();
	
	Renderer *r = Renderer::Instance();
	atlas = new Text("Atlas", "", "../../res/img/PacManSpritesheet.png", color());
	r->LoadTexture(atlas->id, atlas->path);

	blue_block = Rect((r->GetTextureSize("Atlas").x / 8) * 4, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	grey_block = Rect((r->GetTextureSize("Atlas").x / 8) * 7, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	point_block = Rect((r->GetTextureSize("Atlas").x / 8) * 5, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	powerUp_block = Rect((r->GetTextureSize("Atlas").x / 8) * 6, (r->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	black_block = Rect(0, (r->GetTextureSize("Atlas").y / 8) * 7, vec2(128, 128));

	pressSpace = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("PS", "Press space", "", color(255, 255, 255)),
		Text("PS", "Press space", "", color(255, 255, 255)),
		vec2(200, 100));
	toStart = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("TS", "to Start", "", color(255, 255, 255)),
		Text("TS", "to Start", "", color(255, 255, 255)),
		vec2(200, 200));

	fruitsTimes[0] = 0;
	fruitsTimes[1] = 0;
	fruitsTimes[2] = 0;

	Renderer::Instance()->pauseMusic();
}

void Play::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
		case START_GAME:
			if (inputButtons[(int)InputKeys::SPACE])
			{
				sceneState = IS_RUNNING;
			}
			break;

		case IS_RUNNING:
			//Get Inputs in square centre
			//std::cout << pacman->body.x << std::endl;
			if (pacman->getPlayerPosition().x % 35 == 0 && pacman->getPlayerPosition().y % 35 == 0)
			{
				if (inputButtons[InputKeys::UP])
				{
					pacman->lastDirec = InputKeys::UP;
				}
				else if (inputButtons[InputKeys::DOWN])
				{
					pacman->lastDirec = InputKeys::DOWN;
				}
				else if (inputButtons[InputKeys::RIGHT])
				{
					pacman->lastDirec = InputKeys::RIGHT;
				}
				else if (inputButtons[InputKeys::LEFT])
				{
					pacman->lastDirec = InputKeys::LEFT;
				}
			}

			//Move player
			if (canMove())
			{			
				/*system("CLS");
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 20; j++)
					{
						std::cout << m[i][j];
					}
					std::cout << std::endl;
				}*/

				pacman->move();
			}

			if (inputButtons[(int)InputKeys::P])
			{
				sceneState = PAUSED;
			}

			hud.update(score, fruitsTimes[0], fruitsTimes[1], fruitsTimes[2]);
			break;

		case PAUSED:
			if (inputButtons[(int)InputKeys::SPACE])
			{
				sceneState = IS_RUNNING;
			}

			if (inputButtons[(int)InputKeys::ESC])
			{
				sceneState = RETURN_TO_MENU;
			}
			break;

		case GAME_OVER:
			break;

		case RETURN_TO_MENU:
			gameState = MENU;
			break;
	}
}

void Play::readXML()
{
	//Seteo map de chars para colisiones
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++) 
		{
			m[i][j] = 'C';
		}
	}

	m[1][4] = 'S';
	m[18][4] = 'S';
	m[1][16] = 'S';
	m[18][16] = 'S';

	//Copia de XML
	rapidxml::xml_document<> doc; //Documento XML
	std::ifstream file("../../res/files/config.xml"); //Leemos el documento
	std::stringstream buffer; //Creamos un buffer
	buffer << file.rdbuf(); //Le metemos al buffer los strings de XML
	file.close(); //Cerramos la lectura
	std::string content(buffer.str());
	doc.parse<0>(&content[0]); //Pasamos todo al doc

	//Posiciones 
	int x, y;
	rapidxml::xml_node<> *pRoot = doc.first_node();
	rapidxml::xml_node<> *pLevel = pRoot->first_node("Map");
	rapidxml::xml_node<> *pPositions = pRoot->first_node("Positions");
	rapidxml::xml_node<> *pPlayer = pPositions->first_node("Player");
	rapidxml::xml_attribute<> *pAttributes = pPlayer->first_attribute("x");
	x = std::atoi(pAttributes->value()) - 1;
	y = std::atoi(pAttributes->next_attribute()->value()) - 1;
	m[x][y] = 'P';
	pacman = new Player(Rect(vec2(x*35,y*35),vec2(35,35))); //Pacman Init
	std::cout << std::endl;
	/*rapidxml::xml_node<> *pBlinky = pPositions->first_node("Blinky");
	rapidxml::xml_node<> *pInky = pPositions->first_node("Inky");
	rapidxml::xml_node<> *pClyke = pPositions->first_node("Clyke");
	rapidxml::xml_node<> *pPowerUps = pPositions->first_node("PowerUps");
	rapidxml::xml_node<> *pPower = pPowerUps->first_node("Power");*/


	//Mapa
	rapidxml::xml_node<> *pWall = pLevel->first_node("Wall");
	for (; pWall; pWall = pWall->next_sibling())
	{
		int i = 0;
		int j = 0;

		rapidxml::xml_attribute<> *pAttributes = pWall->first_attribute("x");
		i = std::atoi(pAttributes->value());
		j = std::atoi(pAttributes->next_attribute()->value());
		i -= 1;
		j -= 1;
		map[i][j] = { i * 35, j * 35, vec2(35,35) };
		m[i][j] = 'W';
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (m[i][j] == 'C' || m[i][j] == 'S')
			{
				map[i][j] = { i * 35, j * 35, vec2(35,35) };
			}
		}
	}


}

void Play::saveFile()
{
}

void Play::lifes()
{
}

void Play::startMesage()
{
}

bool Play::canMove()
{
	if (pacman->body.x % 35 != 0 || pacman->body.y % 35 != 0) return true;  // Si no está en el centro de una casilla de la grid directamente sabemos que no hanrá colisión
	else
	{
		if (pacman->lastPos.x > 0 && pacman->lastPos.x < 19)
		{
			m[pacman->lastPos.x][pacman->lastPos.y] = ' ';                      // Se borra el icono que habia del jugador en la posición anterior
			if (m[pacman->body.x / 35][pacman->body.y / 35] == 'C') score++;    // Se mira si se tiene que sumar un punto normal
			m[pacman->body.x / 35][pacman->body.y / 35] = 'P';					// Se mete el icono en la posición actual
			pacman->lastPos = vec2(pacman->body.x / 35, pacman->body.y / 35);	// Se actualizad la última posición de la grid donde estaba el jugador
		}

		else
		{
			if (pacman->lastPos.x == 0)
			{
				pacman->body.x = 665;
				if (m[19][pacman->lastPos.y] == 'C')
				{
					m[19][pacman->lastPos.y] == ' ';
					score++;
				}
				pacman->lastPos = vec2(18, pacman->lastPos.y);

			}
			else if (pacman->lastPos.x == 19)
			{
				pacman->body.x = 0;
				if (m[0][pacman->lastPos.y] == 'C')
				{
					m[0][pacman->lastPos.y] == ' ';
					score++;
				}
				pacman->lastPos = vec2(1, pacman->lastPos.y);
			}

			m[pacman->lastPos.x][pacman->lastPos.y] = 'P';
		}

		switch (pacman->lastDirec) // Miramos en la dirección que toca si podemos movernos
		{
		case InputKeys::UP:
			if (m[pacman->lastPos.x][pacman->lastPos.y - 1] != 'W') return true;
			else return false;
			break;
		case InputKeys::DOWN:
			if (m[pacman->lastPos.x][pacman->lastPos.y + 1] != 'W') return true;
			else return false;
			break;
		case InputKeys::LEFT:
			if (m[pacman->lastPos.x - 1][pacman->lastPos.y] != 'W') return true;
			else return false;
			break;
		case InputKeys::RIGHT:
			if (m[pacman->lastPos.x + 1][pacman->lastPos.y] != 'W') return true;
			else return false;
			break;
		default:
			break;
		}
	}
}

void Play::draw()
{
	Renderer *r = Renderer::Instance();
	r->SetRendreDrawColor(color(0, 0, 0));
	pacman->draw();
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (m[i][j] == 'W')
			{
				r->PushSprite("Atlas", blue_block, map[i][j]);
			}
			else if (m[i][j] == 'C')
			{
				r->PushSprite("Atlas", point_block, map[i][j]);
			}
			else if (m[i][j] == 'S')
			{
				r->PushSprite("Atlas", powerUp_block, map[i][j]);
			}
			
		}
	}
	r->PushSprite("Atlas", grey_block, Rect(700, 0, vec2(200,700)));

	//pacman->draw();
	hud.draw();

	if (sceneState == START_GAME)
	{
		r->PushSprite("Atlas", black_block, Rect(0, 0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT)));
		pressSpace.draw();
		toStart.draw();
	}
	else if (sceneState == PAUSED)
	{
		r->PushSprite("Atlas", black_block, Rect(0, 0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT)));
	}

}


Play::~Play()
{
}
