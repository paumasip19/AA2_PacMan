#include "Play.h"

Play::Play()
{
	sceneState = IS_RUNNING;
	rectGame = { 0,0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT) };
	readXML();
	
	Renderer *r = Renderer::Instance();
	atlas = new Text("Blue_Block", "", "../../res/img/PacManSpritesheet.png", color());
	r->LoadTexture(atlas->id, atlas->path);
	blue_block = Rect((r->GetTextureSize("Blue_Block").x / 8) * 4, (r->GetTextureSize("Blue_Block").y / 8) * 6, vec2(128, 128));
	
}

void Play::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
		case START_GAME:
			break;

		case IS_RUNNING:
			//Get Inputs in square centre
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

			break;

		case PAUSED:
			break;

		case GAME_OVER:
			break;

		case RETURN_TO_MENU:
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
	pacman = new Player(Rect(vec2(x*35,y*35),vec2(35,35)));
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
		m[pacman->lastPos.x][pacman->lastPos.y] = ' ';                      // Se borra el icono que habia del jugador en la posición anterior
		m[pacman->body.x / 35][pacman->body.y / 35] = 'P';					// Se mete el icono en la posición actual
		pacman->lastPos = vec2(pacman->body.x / 35, pacman->body.y / 35);	// Se actualizad la última posición de la grid donde estaba el jugador
		
		switch (pacman->lastDirec) // Miramos en la dirección que toca si podemos movernos
		{
			case InputKeys::UP:
				if (m[pacman->lastPos.x][pacman->lastPos.y-1] != 'W') return true;
				else return false;
				break;
			case InputKeys::DOWN:
				if (m[pacman->lastPos.x][pacman->lastPos.y+1] != 'W') return true;
				else return false;
				break;
			case InputKeys::LEFT:
				if (m[pacman->lastPos.x-1][pacman->lastPos.y] != 'W') return true;
				else return false;
				break;
			case InputKeys::RIGHT:
				if (m[pacman->lastPos.x+1][pacman->lastPos.y] != 'W') return true;
				else return false;
				break;
			default:
				break;
		}
	}
}

void Play::updatePoints()
{
}

void Play::draw()
{
	Renderer *r = Renderer::Instance();
	r->SetRendreDrawColor(color(0, 0, 0));
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (m[i][j] == 'W')
			{
				r->PushSprite("Blue_Block", blue_block, map[i][j]);
				//r->PushImage("Blue_Block", map[i][j]);
			}
			
		}
	}
	pacman->draw();

}


Play::~Play()
{
}
