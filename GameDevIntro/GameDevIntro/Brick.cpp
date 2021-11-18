#include "Brick.h"

Brick::Brick(float x, float y, float height, float width, float vx, float vy, const wchar_t* path)
{
	this->coords.x = x;
	this->coords.y = y;
	this->height = height;
	this->width = width;
	this->vx = vx;
	this->vy = vy;
	this->path = path;
}

Brick::Brick()
{
	this->coords.x = 0.0f;
	this->coords.y = 0.0f;
	this->height = 16.0f;
	this->width = 16.0f;
	this->vx = 0.2f;
	this->vy = 0.2f;
	this->path = L"brick.png";
}

