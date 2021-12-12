#include "GameVector.h"
#pragma region Contructor and Decontructor
CGameVector::CGameVector() {

}
CGameVector::CGameVector(float vx, float vy) {
	this->vx = vx;
	this->vy = vy;
}

CGameVector::CGameVector(const CGameVector& v) {
	this->vx = v.vx;
	this->vy = v.vy;
}

CGameVector::~CGameVector() {

}
#pragma endregion

#pragma region Method
void CGameVector::MakeVxIsPositiveValue() {
	if (this->vx < 0) {
		this->vx = -this->vx;
	}
}
void CGameVector::MakeVyIsPositiveValue() {
	if (this->vy < 0) {
		this->vy = -this->vy;
	}
}
void CGameVector::MakeVxIsNegativeValue() {
	if (this->vx > 0) {
		this->vx = -this->vx;
	}
}
void CGameVector::MakeVyIsNegativeValue() {
	if (this->vy > 0) {
		this->vy = -this->vy;
	}
}

void CGameVector::MakeDirectionIsUp() {
	MakeVyIsNegativeValue();
}
void CGameVector::MakeDirectionIsDown() {
	MakeVyIsPositiveValue();
}
void CGameVector::MakeDirectionIsLeft() {
	MakeVxIsNegativeValue();
}
void CGameVector::MakeDirectionIsRight() {
	MakeVxIsPositiveValue();
}
#pragma endregion
