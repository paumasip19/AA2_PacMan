#pragma once
#include "Scene.h"
#include "Button.h"
#include "PowerUp.h"

#include <ctime>

#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <fstream>
#include <sstream>

#include <vector>

class Play : public Scene
{
public:
	Rect rectGame;
	Rect map[20][20];
	Play();

	void update(vec2 mousePos, bool inputButtons[], GameState &gameState);
	void draw();

	~Play();
};

