#pragma once

#include <d3d9.h>
#include <d3dx9.h>

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
	float x, y, height, width, vx, vy;
	const wchar_t * path;
	int status = 0;

	GameObject() {}
	GameObject(float x, float y, float height, float width, float vx, float vy, const wchar_t* path, int status = 0);

	void SetStatus(int status);

	void Update(float x, float y, int height, int width, DWORD dt);

	void MoveUp(float x, float y, int height, int width, DWORD dt);
	void MoveDown(float x, float y, int height, int width, DWORD dt);
	void MoveLeft(float x, float y, int height, int width, DWORD dt);
	void MoveRight(float x, float y, int height, int width, DWORD dt);

	void GoUp(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt);
	void GoDown(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt);
	void GoLeft(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt);
	void GoRight(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt);
	void GoArroundFollowClockwise(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt);
	void GoArroundCounterClockwise(float xWnd, float yWnd, int heightWnd, int widthWnd, DWORD dt);

	bool isCloseToTheTopEdge(float xWnd, float yWnd, int heightWnd, int widthWnd);
	bool isCloseToTheBotEdge(float xWnd, float yWnd, int heightWnd, int widthWnd);
	bool isCloseToTheRightEdge(float xWnd, float yWnd, int heightWnd, int widthWnd);
	bool isCloseToTheLeftEdge(float xWnd, float yWnd, int heightWnd, int widthWnd);
};

