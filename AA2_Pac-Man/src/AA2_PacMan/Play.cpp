#include "Play.h"

Play::Play()
{
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
		case IS_RUNNING:
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

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			std::cout << m[i][j];
		}
		std::cout << std::endl;
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

	//Mapa
	rapidxml::xml_node<> *pRoot = doc.first_node();
	rapidxml::xml_node<> *pLevel = pRoot->first_node("Map");
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
			std::cout << m[i][j];
		}
		std::cout << std::endl;
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

void Play::updatePoints()
{
}

void Play::draw()
{
	Renderer *r = Renderer::Instance();
	//r->SetRendreDrawColor(color(0, 0, 0));
	
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
	//r->PushImage("Blue_Block", rectGame);
}


Play::~Play()
{
}
