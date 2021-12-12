#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CGameCoordinate
{
private:
	float x = 0;
	float y = 0;

public:
	friend class CGameObject;

	// Contructor and Decontructor
	CGameCoordinate();
	CGameCoordinate(float x, float y);
	CGameCoordinate(const CGameCoordinate&c);

	~CGameCoordinate();

	// Get/set property
	float GetX() { return this->x; }
	float GetY() { return this->y; }

	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetCoord(float x, float y) { SetX(x); SetY(y); }


};


