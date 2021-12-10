#include "Mario.h"

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14

void CMario::Update(DWORD dt)
{
	//x += vx * dt;

	float x = this->getCoord().getX() + this->getVx() * dt;
	float y = this->getCoord().getY();
	CCoordinate newCoord = CCoordinate(x, y);

	this->setCoord(newCoord);

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {

		this->setVx(-this->getVx());

		if (x <= 0)
		{
			x = 0;
			this->setCoord(CCoordinate(x, this->getCoord().getY()));
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
			this->setCoord(CCoordinate(x, this->getCoord().getY()));
		}
	}
}
