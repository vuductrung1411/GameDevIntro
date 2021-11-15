#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class GameObject
{
public:
	float x, y, height, width;
	const wchar_t * path;
	DWORD vx, vy;

	void setXY(float x, float y);
	void setVxVy(DWORD vx, DWORD vy);
	void setPath(const wchar_t* path);
};

