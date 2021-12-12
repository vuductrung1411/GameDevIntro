#include "debug.h"
#include "Game.h"
#include "GameObject.h"

#pragma region Contructor and decontructor
/*
	Initialize game object and load a texture
*/
CGameObject::CGameObject(float x, float y, LPDIRECT3DTEXTURE9 tex)
{
	this->coord.SetCoord(x, y);
	this->texture = tex;
}

CGameObject::~CGameObject()
{
	if (texture != NULL) texture->Release();
}
#pragma endregion

#pragma region Checking position property
int BackBufferWidth;
int BackBufferHeight;

void GetBackBuffer() {
	BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();
}

bool CGameObject::isTopEdgeCamera() {
	GetBackBuffer();
	return this->coord.y <= 0;
}

bool CGameObject::isDownEdgeCamera() {
	GetBackBuffer();
	return this->coord.y >= BackBufferHeight - this->height;
}

bool CGameObject::isLeftEdgeCamera() {
	GetBackBuffer();
	return this->coord.x <= 0;
}

bool CGameObject::isRightEdgeCamera() {
	GetBackBuffer();
	return this->coord.x >= BackBufferWidth - this->height;
}
#pragma endregion

#pragma region Move property
void CGameObject::RecheckingAvailableCoordinate() {
	if (isTopEdgeCamera()) {
		this->SetCoordinateIsTopEdge();
	}
	if (isDownEdgeCamera()) {
		this->SetCoordinateIsDownEdge();
	}
	if (isLeftEdgeCamera()) {
		this->SetCoordinateIsLeftEdge();
	}
	if (isRightEdgeCamera()) {
		this->SetCoordinateIsRightEdge();
	}
}

void CGameObject::Move(int direction, DWORD dt) {
	switch (direction)
	{
	case DIRECTION_Free:
		this->coord.x += this->vector.vx * dt;
		this->coord.y += this->vector.vy * dt;
	case DIRECTION_Up:
		this->vector.MakeDirectionIsUp();
		this->coord.y += this->vector.vy * dt;
		break;
	case DIRECTION_Down:
		this->vector.MakeDirectionIsDown();
		this->coord.y += this->vector.vy * dt;
		break;
	case DIRECTION_Left:
		this->vector.MakeDirectionIsLeft();
		this->coord.x += this->vector.vx * dt;
		break;
	case DIRECTION_Right:
		this->vector.MakeDirectionIsRight();
		this->coord.x += this->vector.vx * dt;
		break;
	default:
		break;
	}

	this->RecheckingAvailableCoordinate();
}

void CGameObject::SetCoordinateIsTopEdge() {
	GetBackBuffer();
	this->coord.y = 0;
}
void CGameObject::SetCoordinateIsDownEdge() {
	GetBackBuffer();
	this->coord.y = BackBufferHeight - this->height;
}
void CGameObject::SetCoordinateIsLeftEdge() {
	GetBackBuffer();
	this->coord.x = 0;
}
void CGameObject::SetCoordinateIsRightEdge() {
	GetBackBuffer();
	this->coord.x = BackBufferWidth - this->width;
}

void CGameObject::GoUp(DWORD dt) {
	this->Move(DIRECTION_Up, dt);

	// Nếu ra khỏi màn hình thì cho nó xuất hiện ở đáy màn hình
	if (isTopEdgeCamera())
	{
		this->SetCoordinateIsDownEdge();
	}
}
void CGameObject::GoDown(DWORD dt) {
	this->Move(DIRECTION_Down, dt);

	// Nếu ra khỏi màn hình thì cho nó xuất hiện ở top của màn hình
	if (isDownEdgeCamera())
	{
		this->SetCoordinateIsTopEdge();
	}
}
void CGameObject::GoLeft(DWORD dt) {
	this->Move(DIRECTION_Left, dt);

	// Nếu ra khỏi màn hình thì cho nó xuất hiện ở phía bên phải của màn hình
	if (isLeftEdgeCamera())
	{
		this->SetCoordinateIsRightEdge();
	}
}
void CGameObject::GoRight(DWORD dt) {
	this->Move(DIRECTION_Right, dt);

	// Nếu ra khỏi màn hình thì cho nó xuất hiện ở phía bên trái của màn hình
	if (isRightEdgeCamera())
	{
		this->SetCoordinateIsLeftEdge();
	}
}
void CGameObject::GoRunClockwise(DWORD dt) {
	if (isTopEdgeCamera()) {
		Move(DIRECTION_Right, dt);
	}
	if (isRightEdgeCamera()) {
		Move(DIRECTION_Down, dt);
	}
	if (isDownEdgeCamera()) {
		Move(DIRECTION_Left, dt);
	}
	if (isLeftEdgeCamera()) {
		Move(DIRECTION_Up, dt);
	}
	if (!isTopEdgeCamera() && !isRightEdgeCamera() && !isDownEdgeCamera() && !isLeftEdgeCamera())
	{
		Move(DIRECTION_Right, dt);
	}
}
void CGameObject::GoRunCounterClockwise(DWORD dt) {
	if (isTopEdgeCamera()) {
		Move(DIRECTION_Left, dt);
	}
	if (isLeftEdgeCamera()) {
		Move(DIRECTION_Down, dt);
	}
	if (isDownEdgeCamera()) {
		Move(DIRECTION_Right, dt);
	}
	if (isRightEdgeCamera()) {
		Move(DIRECTION_Up, dt);
	}
	if (!isTopEdgeCamera() && !isRightEdgeCamera() && !isDownEdgeCamera() && !isLeftEdgeCamera())
	{
		Move(DIRECTION_Left, dt);
	}
}
#pragma endregion


#pragma region Method
void CGameObject::Update(DWORD dt) {
	switch (this->status)
	{
	case STATUS_Stand_still:
		break;
	case STATUS_Follow_keystate:
		break;
	case STATUS_Go_up:
		GoUp(dt);
		break;
	case STATUS_Go_down:
		GoDown(dt);
		break;
	case STATUS_Go_left:
		GoLeft(dt);
		break;
	case STATUS_Go_right:
		GoRight(dt);
		break;
	case STATUS_Run_clockwise:
		GoRunClockwise(dt);
		break;
	case STATUS_Run_counter_clockwise:
		GoRunCounterClockwise(dt);
		break;
	default:
		break;
	}
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(this->coord.x, this->coord.y, texture);
}
#pragma endregion