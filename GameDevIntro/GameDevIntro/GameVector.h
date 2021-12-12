#pragma once
#include <algorithm>  

enum DIRECTION {
	DIRECTION_Free,
	DIRECTION_Up,
	DIRECTION_Down,
	DIRECTION_Left,
	DIRECTION_Right
};

class CGameVector
{
	float vx, vy;
public:
	friend class CGameObject;

	// Contructor and Decontructor
	CGameVector();
	CGameVector(float vx, float vy);
	CGameVector(const CGameVector& v);

	~CGameVector();

	// Get/set property
	float GetVx() { return this->vx; }
	float GetVy() { return this->vy; }

	void SetVx(float vx) { this->vx = vx; }
	void SetVy(float vy) { this->vy = vy; }
	void SetVector(float vx, float vy) { SetVx(vx); SetVy(vy); }

	// Method
	void MakeVxIsPositiveValue();
	void MakeVyIsPositiveValue();
	void MakeVxIsNegativeValue();
	void MakeVyIsNegativeValue();

	void MakeDirectionIsUp();
	void MakeDirectionIsDown();
	void MakeDirectionIsLeft();
	void MakeDirectionIsRight();
};

