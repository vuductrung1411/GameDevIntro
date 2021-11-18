#pragma once

#include "Coords.h"

class Camera
{
private:
	Camera() {}

public:
	static Coords coords;
	static int height;
	static int width;
	static void SetValue(Coords c, int h, int w);
};

