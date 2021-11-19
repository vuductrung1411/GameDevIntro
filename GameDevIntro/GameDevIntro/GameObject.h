#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Coords.h"

#include "Camera.h"

enum Status
{
	STATUS_STAND,	
	STATUS_FOLLOW_KEYSTATE,
	STATUS_GO_UP,
	STATUS_GO_DOWN,
	STATUS_GO_LEFT,
	STATUS_GO_RIGHT,
	STATUS_GO_AROUND_FOLLOW_CLOCKWISE,
	STATUS_GO_AROUND_COUNTER_CLOCKWISE,
	STATUS_HITTING_WALL
};

class GameObject
{
public:
	float height, width, vx, vy;
	const wchar_t * path;
	int status = 0;
	Coords coords;

	Camera camera;

	GameObject() {}
	GameObject(Camera camera, float x, float y, float height, float width, float vx, float vy, const wchar_t* path, int status = 0);

	void SetStatus(int status);
	void SetCamera(Camera camera);

	void Update(DWORD dt); 

	void MoveUp(DWORD dt);
	void MoveDown(DWORD dt);
	void MoveLeft(DWORD dt); 
	void MoveRight(DWORD dt); 

	void GoUp(DWORD dt);
	void GoDown(DWORD dt);
	void GoLeft(DWORD dt);
	void GoRight(DWORD dt);
	void GoArroundFollowClockwise(DWORD dt);
	void GoArroundCounterClockwise(DWORD dt);

	bool isCloseToTheTopEdge();
	bool isCloseToTheBotEdge();
	bool isCloseToTheRightEdge();
	bool isCloseToTheLeftEdge();
};

