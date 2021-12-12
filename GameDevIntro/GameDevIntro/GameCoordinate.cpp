#include "GameCoordinate.h"

#pragma region Contructor and Decontructor
CGameCoordinate::CGameCoordinate() {

}
CGameCoordinate::CGameCoordinate(float x, float y) {
	this->x = x;
	this->y = y;
}

CGameCoordinate::CGameCoordinate(const CGameCoordinate& c) {
	this->x = c.x;
	this->y = c.y;
}

CGameCoordinate::~CGameCoordinate() {

}
#pragma endregion

