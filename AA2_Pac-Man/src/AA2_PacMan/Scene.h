#include "Types.h"
#include <fstream>

#pragma once
class Scene
{	
public:
	SceneState sceneState;

	Scene();

	virtual void update() = 0;
	virtual void draw() = 0;
	
	~Scene();

};

