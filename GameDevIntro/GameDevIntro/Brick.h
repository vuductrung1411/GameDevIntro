#pragma once
#include "GameObject.h"

class Brick :
    public GameObject
{
public:

    void RunArroundFollowClockwise(int WindowHeight, int WindowWidth, DWORD dt);
    void RunArroundCounterClockwise();

    void Update(DWORD dt);
};

