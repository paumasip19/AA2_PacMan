#include <SDL.h>
#include "Types.h"
#pragma once

class Inputs
{
public:
	bool keyboardPressed[(int)InputKeys::COUNT];
	bool keyboardKeyDown[(int)InputKeys::COUNT];
	
	vec2 mouseCoords;

	Inputs();

	void SetKeyValue(InputKeys key, bool value);
	void SetFalseKeyDown();
	void SetFalseKeyPressed();
	void inputHandle(bool &isRunning);

	~Inputs();
};

