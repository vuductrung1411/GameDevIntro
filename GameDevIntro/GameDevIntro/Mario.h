#pragma once

#include "GameObject.h"

typedef CGameObject* LPGAMEOBJECT;

class CMario : public CGameObject
{
public:
	CMario(float x, float y, float vx, LPDIRECT3DTEXTURE9 texture) :CGameObject(x, y, texture)
	{
		this->setVx(vx);
	};
	void Update(DWORD dt);
};
