#pragma once
#include "GameObject.h"

class Brick :
    public GameObject
{
public:

    Brick();
    Brick(float x, float y, float height, float width, float vx, float vy, const wchar_t* path);

};

