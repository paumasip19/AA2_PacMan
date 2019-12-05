#include "Types.h"
#include <fstream>

#pragma once
class Scene
{	
public:
	SceneState sceneState;

	Scene();

	virtual void update(vec2 mousePos, bool inputButtons[], GameState &gameState) = 0;
	virtual void draw() = 0;
	
	~Scene();

};

