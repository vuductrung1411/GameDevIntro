#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CCoordinate
{
private:
	float x = 0;
	float y = 0;

public:
	// Contructor and Decontructor
	CCoordinate();
	CCoordinate(float x, float y);
	CCoordinate(const CCoordinate &c);

	~CCoordinate();

	// Get/set property
	float getX() { return this->x; }
	float getY() { return this->y; }

	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	// Method
	void goUp(DWORD distance);
	void goDown(DWORD distance);
	void goLeft(DWORD distance);
	void goRight(DWORD distance);
};

