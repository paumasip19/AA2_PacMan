#include "Play.h"

Play::Play()
{
	sceneState = START_GAME;
	rectGame = { 0,0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT) };
	numDots = 0;
	readXML();
	
	atlas = new Text("Atlas", "", "../../res/img/PacManSpritesheet.png", color());
	Renderer::Instance()->LoadTexture(atlas->id, atlas->path);

	blue_block = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 4, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	grey_block = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 7, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	point_block = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 5, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	powerUp_block = Rect((Renderer::Instance()->GetTextureSize("Atlas").x / 8) * 6, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 6, vec2(128, 128));
	black_block = Rect(0, (Renderer::Instance()->GetTextureSize("Atlas").y / 8) * 7, vec2(128, 128));

	pressSpace = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("PS", "Press space", "", color(255, 255, 255)),
		Text("PS", "Press space", "", color(255, 255, 255)),
		vec2(280, 270));
	toStart = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("TS", "to Start", "", color(255, 255, 255)),
		Text("TS", "to Start", "", color(255, 255, 255)),
		vec2(320, 370));

	PrSpace = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("PrS", "Press Space", "", color(255, 255, 255)),
		Text("PrS", "Press Space", "", color(255, 255, 255)),
		vec2(280, 220));

	ToResume = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("TR", "to resume", "", color(255, 255, 255)),
		Text("TR", "to resume", "", color(255, 255, 255)),
		vec2(300, 320));

	soundOn = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("sOnNormal", "Sound On", "", color(255, 0, 0)),
		Text("sOnHover", "Sound On", "", color(0, 255, 0)),
		vec2(310, 500));

	soundOff = Button(Font("PacFont", "../../res/ttf/PAC-FONT.ttf"),
		Text("sOffNormal", "Sound Off", "", color(255, 0, 0)),
		Text("sOffHover", "Sound Off", "", color(0, 255, 0)),
		vec2(300, 500));

	fruitsTimes[0] = 0;
	fruitsTimes[1] = 0;
	fruitsTimes[2] = 0;

	sound = Renderer::Instance()->isMusicOn();
	canClick = true;
}

void Play::update(vec2 mousePos, bool inputButtons[], GameState &gameState)
{
	switch (sceneState)
	{
		case START_GAME:
			system("CLS");
			if (inputButtons[(int)InputKeys::SPACE])
			{
				sceneState = IS_RUNNING;
			}
			
			if (inputButtons[(int)InputKeys::ESC])
			{
				sceneState = RETURN_TO_MENU;
			}
			fruit->canAppear = true;
			fruit->isVisible = false;
			break;

		case IS_RUNNING:
			//std::cout << numDots << std::endl;
			//Get Inputs in square centre

			if (pacman->getPlayerPosition().x % 35 == 0 && pacman->getPlayerPosition().y % 35 == 0)
			{
				if (inputButtons[InputKeys::UP])
				{
					pacman->lastDirec = InputKeys::UP;
					inkyF->newLastDirec = InputKeys::UP;
					clydeF->newLastDirec = InputKeys::DOWN;
				}
				else if (inputButtons[InputKeys::DOWN])
				{
					pacman->lastDirec = InputKeys::DOWN;
					inkyF->newLastDirec = InputKeys::DOWN;
					clydeF->newLastDirec = InputKeys::UP;
				}
				else if (inputButtons[InputKeys::RIGHT])
				{
					pacman->lastDirec = InputKeys::RIGHT;
					inkyF->newLastDirec = InputKeys::RIGHT;
					clydeF->newLastDirec = InputKeys::LEFT;
				}
				else if (inputButtons[InputKeys::LEFT])
				{
					pacman->lastDirec = InputKeys::LEFT;
					inkyF->newLastDirec = InputKeys::LEFT;
					clydeF->newLastDirec = InputKeys::RIGHT;
				}
			}

			//Move Inky
			if (canEnemyMove(EnemyType::INKY))
			{
				inkyF->Move();
			}

			inkyF->animationSprite();
			inkyF->canDie();
			inkyF->die();

			//Move Clyde
			if (canEnemyMove(EnemyType::CLYDE))
			{
				clydeF->Move();				
			}

			clydeF->animationSprite();
			clydeF->canDie();
			clydeF->die();

			//Move Blinky
			if (canEnemyMove(EnemyType::BLINKY))
			{
				blinkyF->Move();
			}

			blinkyF->animationSprite();
			blinkyF->canDie();
			blinkyF->die();

			//Move player
			if (canMove())
			{			
				pacman->move();
				pacman->animationSprite();
			}
			pacman->deathAnimation();

			//Fruits Update
			fruit->update(pacman->body, score, fruitsTimes[0], fruitsTimes[1], fruitsTimes[2]);

			//Score Update
			hud.update(score, fruitsTimes[0], fruitsTimes[1], fruitsTimes[2], pacman->lifes);

			// Chech player dead
			playerKilled();

			//Player spends 1 life
			if (pacman->dead)
			{
				fruit->canAppear = false;
				fruit->isVisible = false;
				// Init Pos Player
				m[pacman->lastPos.x][pacman->lastPos.y] = ' ';
				m[pacman->firstPos.x][pacman->firstPos.y] = 'P';
				pacman->body.x = pacman->firstPos.x * 35;
				pacman->body.y = pacman->firstPos.y * 35;

				// Init Pos Inky
				m[inkyF->lastPos.x][inkyF->lastPos.y] = ' ';
				m[inkyF->initPos.x][inkyF->initPos.y] = 'F';
				inkyF->body.x = inkyF->initPos.x * 35;
				inkyF->body.y = inkyF->initPos.y * 35;

				// Init Pos Clyke
				m[clydeF->lastPos.x][clydeF->lastPos.y] = ' ';
				m[clydeF->initPos.x][clydeF->initPos.y] = 'F';
				clydeF->body.x = clydeF->initPos.x * 35;
				clydeF->body.y = clydeF->initPos.y * 35;

				// Init Pos Blinky
				m[blinkyF->lastPos.x][blinkyF->lastPos.y] = ' ';
				m[blinkyF->initPos.x][blinkyF->initPos.y] = 'F';
				blinkyF->body.x = blinkyF->initPos.x * 35;
				blinkyF->body.y = blinkyF->initPos.y * 35;

				
				pacman->dead = false;
				sceneState = START_GAME;

			}

			//PAUSED SCREEN
			if (inputButtons[(int)InputKeys::P])
			{
				sceneState = PAUSED;
			}
			
			//GAME OVER
			if (numDots == 0 || pacman->fullDeath)
			{
				sceneState = GAME_OVER;
			}

			break;

		case PAUSED:

			if (canClick)
			{
				if (sound)
				{
					if (soundOn.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
					{
						sound = false;
						Renderer::Instance()->pauseMusic();
						canClick = false;
					}
				}
				else
				{
					if (soundOff.hover(mousePos, inputButtons[(int)InputKeys::MOUSE_LEFT]))
					{
						sound = true;
						Renderer::Instance()->playMusic();
						canClick = false;
					}

				}
			}
			else if (!inputButtons[(int)InputKeys::MOUSE_LEFT]) canClick = true;

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
			std::cout << "***** GAME OVER *****" << std::endl;
			std::cout << "Inserte el nombre (Utiliza solo 4 letras): " << std::endl;
			std::cin >> name;
			if (name.size() > 4)
			{
				system("CLS");
				std::cout << "Numero de caracteres incorrecto!!!" << std::endl;				
				sceneState = GAME_OVER;
			}
			else
			{
				system("CLS");
				saveFile();
				gameState = RANKING;
			}

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
			numDots++;
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

	//Player
	rapidxml::xml_node<> *pPlayer = pPositions->first_node("Player");
	rapidxml::xml_attribute<> *pAttributes = pPlayer->first_attribute("x");
	x = std::atoi(pAttributes->value()) - 1;
	y = std::atoi(pAttributes->next_attribute()->value()) - 1;
	m[x][y] = 'P';
	numDots--;
	pacman = new Player(Rect(vec2(x * 35, y * 35), vec2(35, 35))); //Pacman Init

	//Inky
	rapidxml::xml_node<> *pInky = pPositions->first_node("Inky");
	pAttributes = pInky->first_attribute("x");
	x = std::atoi(pAttributes->value()) - 1;
	y = std::atoi(pAttributes->next_attribute()->value()) - 1;
	inkyF = new Inky(vec2(x * 35, y * 35)); //Inky Init

	//Clyde
	rapidxml::xml_node<> *pClyke = pPositions->first_node("Clyke");
	pAttributes = pClyke->first_attribute("x");
	x = std::atoi(pAttributes->value()) - 1;
	y = std::atoi(pAttributes->next_attribute()->value()) - 1;
	clydeF = new Clyde(vec2(x * 35, y * 35)); //Clyde Init

	//Blinky
	rapidxml::xml_node<> *pBlinky = pPositions->first_node("Blinky");
	pAttributes = pBlinky->first_attribute("x");
	x = std::atoi(pAttributes->value()) - 1;
	y = std::atoi(pAttributes->next_attribute()->value()) - 1;
	blinkyF = new Blinky(vec2(x * 35, y * 35)); //Blinky Init

	//Fruits
	fruit = new Fruit(Rect(vec2(pacman->body.x, pacman->body.y), vec2(35, 35)));

	//PowerUps
	rapidxml::xml_node<> *pPowerUps = pPositions->first_node("PowerUps");
	rapidxml::xml_node<> *pPower = pPowerUps->first_node("Power");

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
		numDots--;
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
	std::ofstream salida("../../res/files/ranking.bin", std::ios::out | std::ios::app | std::ios::binary);
	size_t len;

	len = name.size();
	salida.write(reinterpret_cast<char *>(&len), sizeof(size_t));
	salida.write(name.c_str(), len);

	salida.write(reinterpret_cast<char *>(&score), sizeof(score));

	salida.close();
}

bool Play::canMove()
{
	if (pacman->body.x % 35 != 0 || pacman->body.y % 35 != 0) return true;  // Si no está en el centro de una casilla de la grid directamente sabemos que no hanrá colisión
	else
	{
		if (pacman->lastPos.x > 0 && pacman->lastPos.x < 19)
		{
			m[pacman->lastPos.x][pacman->lastPos.y] = ' ';                      // Se borra el icono que habia del jugador en la posición anterior
			if (m[pacman->body.x / 35][pacman->body.y / 35] == 'C')				// Se mira si se tiene que sumar un punto
			{
				numDots--;
				score++;    
			}
			if (m[pacman->body.x / 35][pacman->body.y / 35] == 'S')				// Se mira si se tiene que sumar un powerUp
			{
				numDots--;
				score++;
				inkyF->isVulnerable = true;
				inkyF->beginVulnerable = clock();
				clydeF->isVulnerable = true;
				clydeF->beginVulnerable = clock();
				blinkyF->isVulnerable = true;
				blinkyF->beginVulnerable = clock();
			}
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
					m[19][pacman->lastPos.y] = ' ';
					score++;
					numDots--;
				}
				pacman->lastPos = vec2(18, pacman->lastPos.y);

			}
			else if (pacman->lastPos.x == 19)
			{
				pacman->body.x = 0;
				if (m[0][pacman->lastPos.y] == 'C')
				{
					m[0][pacman->lastPos.y] = ' ';
					score++;
					numDots--;
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
			return false;
			break;
		}
	}
}

bool Play::canEnemyMove(int _type)
{
	switch (_type)
	{
		case EnemyType::INKY:
			if (inkyF->body.x % 35 != 0 || inkyF->body.y % 35 != 0) { return true; }  // Si no está en el centro de una casilla de la grid directamente sabemos que no hanrá colisión
			else
			{
				inkyF->lastDirec = inkyF->newLastDirec;
				if (inkyF->lastPos.x > 0 && inkyF->lastPos.x < 19)
				{
					inkyF->lastPos = vec2(inkyF->body.x / 35, inkyF->body.y / 35);	    // Se actualiza la última posición de la grid donde estaba el fantasma
				}

				else
				{
					if (inkyF->lastPos.x == 0)
					{
						inkyF->body.x = 665;
						inkyF->lastPos = vec2(18, inkyF->lastPos.y);

					}
					else if (inkyF->lastPos.x == 19)
					{
						inkyF->body.x = 0;
						inkyF->lastPos = vec2(1, inkyF->lastPos.y);
					}
				}

				switch (inkyF->lastDirec) // Miramos en la dirección que toca si podemos movernos
				{
				case InputKeys::UP:
					if (m[inkyF->lastPos.x][inkyF->lastPos.y - 1] != 'W') return true;
					else return false;
					break;
				case InputKeys::DOWN:
					if (m[inkyF->lastPos.x][inkyF->lastPos.y + 1] != 'W') return true;
					else return false;
					break;
				case InputKeys::LEFT:
					if (m[inkyF->lastPos.x - 1][inkyF->lastPos.y] != 'W') return true;
					else return false;
					break;
				case InputKeys::RIGHT:
					if (m[inkyF->lastPos.x + 1][inkyF->lastPos.y] != 'W') return true;
					else return false;
					break;
				default:
					break;
				}
			}
			break;

		case EnemyType::CLYDE:
			if (clydeF->body.x % 35 != 0 || clydeF->body.y % 35 != 0) return true;  // Si no está en el centro de una casilla de la grid directamente sabemos que no hará colisión
			else
			{
				clydeF->lastDirec = clydeF->newLastDirec;
				if (clydeF->lastPos.x > 0 && clydeF->lastPos.x < 19)
				{
					clydeF->lastPos = vec2(clydeF->body.x / 35, clydeF->body.y / 35);	// Se actualiza la última posición de la grid donde estaba el fantasma
				}

				else
				{
					if (clydeF->lastPos.x == 0)
					{
						clydeF->body.x = 665;
						clydeF->lastPos = vec2(18, clydeF->lastPos.y);

					}
					else if (clydeF->lastPos.x == 19)
					{
						clydeF->body.x = 0;
						clydeF->lastPos = vec2(1, clydeF->lastPos.y);
					}
				}

				switch (clydeF->lastDirec) // Miramos en la dirección que toca si podemos movernos
				{
				case InputKeys::UP:
					if (m[clydeF->lastPos.x][clydeF->lastPos.y - 1] != 'W') return true;
					else return false;
					break;
				case InputKeys::DOWN:
					if (m[clydeF->lastPos.x][clydeF->lastPos.y + 1] != 'W') return true;
					else return false;
					break;
				case InputKeys::LEFT:
					if (m[clydeF->lastPos.x - 1][clydeF->lastPos.y] != 'W') return true;
					else return false;
					break;
				case InputKeys::RIGHT:
					if (m[clydeF->lastPos.x + 1][clydeF->lastPos.y] != 'W') return true;
					else return false;
					break;
				default:
					break;
				}
			}
			break;

		case EnemyType::BLINKY:
			if (blinkyF->body.x % 35 != 0 || blinkyF->body.y % 35 != 0) { return true; }  // Si no está en el centro de una casilla de la grid directamente sabemos que no hanrá colisión
			else
			{
				//  blinkyF->lastDirec;    | Dirección en la que se mueve ahora

				// Actualizamos la posición
				if (blinkyF->lastPos.x > 0 && blinkyF->lastPos.x < 19)
				{
					blinkyF->lastPos = vec2(blinkyF->body.x / 35, blinkyF->body.y / 35);	    // Se actualiza la última posición de la grid donde estaba el fantasma
				}
				// Teleportación del túnel
				else
				{
					if (blinkyF->lastPos.x == 0)
					{
						blinkyF->body.x = 665;
						blinkyF->lastPos = vec2(18, blinkyF->lastPos.y);

					}
					else if (blinkyF->lastPos.x == 19)
					{
						blinkyF->body.x = 0;
						blinkyF->lastPos = vec2(1, blinkyF->lastPos.y);
					}
				}

				int random = rand() % 3 + 1;
				bool notWall = false;
				int posibleDirecs = 0;

				switch (blinkyF->lastDirec)
				{
					case InputKeys::UP:

						if (m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] != 'W') posibleDirecs++;

						if (posibleDirecs > 1 || m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] == 'W')
						{
							while (!notWall)
							{
								if (random == 1)
								{
									if (m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::LEFT;
									}
									else random = rand() % 3 + 1;
								}
								else if (random == 2)
								{
									if (m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::RIGHT;
									}
									else random = rand() % 3 + 1;
								}
								else
								{
									if (m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::UP;
									}
									else random = rand() % 3 + 1;
								}
							}
						}
						
						break;

					case InputKeys::DOWN:

						if (m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] != 'W') posibleDirecs++;

						if (posibleDirecs > 1 || m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] == 'W')
						{
							while (!notWall)
							{
								if (random == 1)
								{
									if (m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::LEFT;
									}
									else random = rand() % 3 + 1;
								}
								else if (random == 2)
								{
									if (m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::RIGHT;
									}
									else random = rand() % 3 + 1;
								}
								else
								{
									if (m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::DOWN;
									}
									else random = rand() % 3 + 1;
								}
							}
						}

						break;

					case InputKeys::LEFT:

						if (m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] != 'W') posibleDirecs++;

						if (posibleDirecs > 1 || m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] == 'W')
						{
							while (!notWall)
							{
								if (random == 1)
								{
									if (m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::LEFT;
									}
									else random = rand() % 3 + 1;
								}
								else if (random == 2)
								{
									if (m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::UP;
									}
									else random = rand() % 3 + 1;
								}
								else
								{
									if (m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::DOWN;
									}
									else random = rand() % 3 + 1;
								}
							}
						}

						break;

					case InputKeys::RIGHT:

						if (m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] != 'W') posibleDirecs++;
						if (m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] != 'W') posibleDirecs++;

						if (posibleDirecs > 1 || m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] == 'W')
						{
							while (!notWall)
							{
								if (random == 1)
								{
									if (m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::RIGHT;
									}
									else random = rand() % 3 + 1;
								}
								else if (random == 2)
								{
									if (m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::UP;
									}
									else random = rand() % 3 + 1;
								}
								else
								{
									if (m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] != 'W')
									{
										notWall = true;
										blinkyF->lastDirec = InputKeys::DOWN;
									}
									else random = rand() % 3 + 1;
								}
							}
						}
						break;

					default:
						break;
				}

				// Miramos en la dirección que toca si podemos movernos
				switch (blinkyF->lastDirec)
				{
				case InputKeys::UP:
					if (m[blinkyF->lastPos.x][blinkyF->lastPos.y - 1] != 'W') return true;
					else return false;
					break;
				case InputKeys::DOWN:
					if (m[blinkyF->lastPos.x][blinkyF->lastPos.y + 1] != 'W') return true;
					else return false;
					break;
				case InputKeys::LEFT:
					if (m[blinkyF->lastPos.x - 1][blinkyF->lastPos.y] != 'W') return true;
					else return false;
					break;
				case InputKeys::RIGHT:
					if (m[blinkyF->lastPos.x + 1][blinkyF->lastPos.y] != 'W') return true;
					else return false;
					break;
				default:
					break;
				}
			}
			break;

		default:
			return false;
			break;
	}
}

void Play::playerKilled()
{
	if (abs(pacman->body.x - inkyF->body.x) < 10 && abs(pacman->body.y - inkyF->body.y) < 10)
	{
		if (!inkyF->isVulnerable)
		{
			pacman->dead = true;
			pacman->lifes--;
		}
		else
		{
			inkyF->beginDead = clock();
			score += 10;
			inkyF->dead = true;
			inkyF->body = Rect(vec2(3000, 3000), vec2(35, 35));
		}
		
	}
	else if (abs(pacman->body.x - clydeF->body.x) < 10 && abs(pacman->body.y - clydeF->body.y) < 10)
	{
		if (!clydeF->isVulnerable)
		{
			pacman->dead = true;
			pacman->lifes--;
		}
		else
		{
			clydeF->beginDead = clock();
			score += 15;
			clydeF->dead = true;
			clydeF->body = Rect(vec2(3000, 3000), vec2(35, 35));
		}
	}
	else if (abs(pacman->body.x - blinkyF->body.x) < 10 && abs(pacman->body.y - blinkyF->body.y) < 10)
	{
		if (!blinkyF->isVulnerable)
		{
			pacman->dead = true;
			pacman->lifes--;
		}
		else
		{
			blinkyF->beginDead = clock();
			score += 25;
			blinkyF->dead = true;
			blinkyF->body = Rect(vec2(3000, 3000), vec2(35, 35));
		}
	}
}

void Play::draw()
{
	Renderer::Instance()->SetRendreDrawColor(color(0, 0, 0));
	pacman->draw();
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (m[i][j] == 'W')
			{
				Renderer::Instance()->PushSprite("Atlas", blue_block, map[i][j]);
			}
			else if (m[i][j] == 'C')
			{
				Renderer::Instance()->PushSprite("Atlas", point_block, map[i][j]);
			}
			else if (m[i][j] == 'S')
			{
				Renderer::Instance()->PushSprite("Atlas", powerUp_block, map[i][j]);
			}
			
		}
	}
	pacman->draw();
	inkyF->draw();
	clydeF->draw();
	blinkyF->draw();
	fruit->draw();
	Renderer::Instance()->PushSprite("Atlas", grey_block, Rect(700, 0, vec2(200,700)));

	hud.draw();

	if (sceneState == START_GAME)
	{
		Renderer::Instance()->PushSprite("Atlas", black_block, Rect(0, 0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT)));
		pressSpace.draw();
		toStart.draw();
	}
	else if (sceneState == PAUSED)
	{
		Renderer::Instance()->PushSprite("Atlas", black_block, Rect(0, 0, vec2(SCREEN_WIDTH, SCREEN_HEIGHT)));
		PrSpace.draw();
		ToResume.draw();

		if (sound) soundOn.draw();
		else soundOff.draw();
	}
}


Play::~Play()
{
}
