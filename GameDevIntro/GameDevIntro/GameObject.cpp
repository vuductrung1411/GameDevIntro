#include "GameObject.h"

void GameObject::setXY(float x, float y)
{
	this->x = x;
	this->y = y;
}

void GameObject::setPath(const wchar_t* path)
{
	this->path = path;
}

void GameObject::setVxVy(DWORD vx, DWORD vy)
{
	this->vx = vx;
	this->vy = vy;
}