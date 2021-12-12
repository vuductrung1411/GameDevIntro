#pragma once

#include "Game.h"
#include "GameCoordinate.h"
#include "GameVector.h"

#include <Windows.h>
#include <d3dx9.h>

enum STATUS_LIST {
	STATUS_Stand_still,
	STATUS_Follow_keystate,
	STATUS_Go_up,
	STATUS_Go_down,
	STATUS_Go_left,
	STATUS_Go_right,
	STATUS_Run_clockwise,
	STATUS_Run_counter_clockwise
};

class CGameObject
{
protected:
	CGameCoordinate coord;
	CGameVector vector;
	float height;
	float width;
	int status = STATUS_Stand_still;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object. 
	// For now, just a pointer to a single texture
	LPDIRECT3DTEXTURE9 texture;
public:
	// Contructor and decontructor
	CGameObject(float x = 0.0f, float y = 0.0f, LPDIRECT3DTEXTURE9 texture = NULL);

	~CGameObject();

	// Get/set property
	CGameCoordinate GetCoord() { return this->coord; }
	CGameVector GetVector() { return this->vector; }
	int GetStatus() { return this->status; }

	void SetStatus(int status) { this->status = status; }

	// Method
	virtual void Update(DWORD dt);
	virtual void Render();

	// Move property
	void Move(int direction, DWORD dt);
	void RecheckingAvailableCoordinate();
	void GoUp(DWORD dt);
	void GoDown(DWORD dt);
	void GoLeft(DWORD dt);
	void GoRight(DWORD dt);
	void GoRunClockwise(DWORD dt); 
	void GoRunCounterClockwise(DWORD dt);
	
	void SetCoordinateIsTopEdge();
	void SetCoordinateIsDownEdge();
	void SetCoordinateIsLeftEdge();
	void SetCoordinateIsRightEdge();

	// Checking position property
	bool isTopEdgeCamera();
	bool isDownEdgeCamera();
	bool isLeftEdgeCamera();
	bool isRightEdgeCamera();
};
