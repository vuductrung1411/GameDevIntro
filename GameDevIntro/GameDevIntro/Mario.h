#pragma once

#include "GameObject.h"

typedef CGameObject* LPGAMEOBJECT;

#define MARIO_TEXTURE_PATH L"mario.png"

#define MARIO_WIDTH 14

#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f

class CMario : public CGameObject
{
	void SetDefineValue() {
		this->height = this->width = MARIO_WIDTH;
		this->vector.SetVector(MARIO_START_VX, MARIO_START_VX);
		this->status = STATUS_Run_counter_clockwise;
	}
public:
	CMario(float x, float y) :CGameObject(x, y, CGame::GetInstance()->LoadTexture(MARIO_TEXTURE_PATH)) { 
		SetDefineValue();
	};
	CMario() : CGameObject(MARIO_START_X, MARIO_START_Y, CGame::GetInstance()->LoadTexture(MARIO_TEXTURE_PATH)) { 
		SetDefineValue();
	};

	//void Update(DWORD dt);


};
