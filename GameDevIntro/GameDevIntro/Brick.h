#pragma once
#include "GameObject.h"

#define BRICK_TEXTURE_PATH L"brick.png"

#define BRICK_X 10.0f
#define BRICK_Y 100.0f
#define BRICK_VX 0.1f

#define BRICK_WIDTH 14.0f

class CBrick :
    public CGameObject
{
    void SetDefineValue() {
        this->height = this->width = BRICK_WIDTH;
        this->vector.SetVector(BRICK_VX, BRICK_VX);
    }
public:
    CBrick(float x, float y) : CGameObject(x, y, CGame::GetInstance()->LoadTexture(BRICK_TEXTURE_PATH)) { 
        SetDefineValue();
    };
    CBrick() : CGameObject(BRICK_X, BRICK_Y, CGame::GetInstance()->LoadTexture(BRICK_TEXTURE_PATH)) { 
        SetDefineValue();
    };

    void Update(DWORD dt);
};

