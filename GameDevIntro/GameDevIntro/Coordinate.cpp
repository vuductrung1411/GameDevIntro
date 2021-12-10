#include "Coordinate.h"

#pragma region Contructor and Decontructor
CCoordinate::CCoordinate() {

}
CCoordinate::CCoordinate(float x, float y) {
	this->x = x;
	this->y = y;
}

CCoordinate::CCoordinate(const CCoordinate& c) {
	this->x = c.x;
	this->y = c.y;
}

CCoordinate::~CCoordinate() {

}
#pragma endregion

#pragma region Method
void CCoordinate::goUp(DWORD distance = 1.0f) {
	this->y -= distance;
}

void CCoordinate::goDown(DWORD distance = 1.0f) {
	this->y += distance;
}

void CCoordinate::goLeft(DWORD distance = 1.0f) {
	this->x -= distance;
}

void CCoordinate::goRight(DWORD distance = 1.0f) {
	this->x += distance;
}
#pragma endregion
