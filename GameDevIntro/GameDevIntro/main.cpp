#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#include "Brick.h"
#include "Camera.h"

#define WINDOW_CLASS_NAME L"SampleWindow" 
#define WINDOW_TITLE L"Blaster Master"		
#define WINDOW_ICON_PATH L"BlasterMaster.ico" 

HWND hWnd = 0;

#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define MAX_FRAME_RATE 120

LPDIRECT3D9 d3d = NULL;						// Direct3D handle
LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

LPDIRECT3DSURFACE9 backBuffer = NULL;
int BackBufferWidth = 0;
int BackBufferHeight = 0;

LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D images 

LPDIRECT3DTEXTURE9 texBrick;				// Texture object to store brick image

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Brick brick;
	Brick br;

	br.x = 50.0f;
	br.y = 50.0f;
	//br.path = L"BlasterMaster.png";

	brick.SetStatus(STATUS_GO_AROUND_FOLLOW_CLOCKWISE);
	//br.SetStatus(STATUS_GO_RIGHT);

	Camera camera;

	camera.hWnd = camera.CreateCamera(hInstance, nCmdShow, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (camera.hWnd == 0) return 0;

	camera.InitDirectX();

	camera.LoadResources(brick);
	camera.LoadResources(br);
	
	camera.Run(brick, br);

	camera.Cleanup();

	return 0;
}