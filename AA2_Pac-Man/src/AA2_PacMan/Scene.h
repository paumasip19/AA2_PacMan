#include "Types.h"
#include <fstream>

enum SceneState {};
#pragma once
class Scene
{	
public:
	SceneState lastState;

	Scene();
	virtual void loopScene() = 0;
	virtual void draw() = 0;
	~Scene();
};

