#pragma once

#include "Coords.h"

class Camera
{
private:
	
public:

	Camera() {}
	Camera(Coords c, int h, int w);

	Coords coords;
	int height;
	int width;
};

