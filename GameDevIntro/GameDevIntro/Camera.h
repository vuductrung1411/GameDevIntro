#pragma once

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

#define WINDOW_CLASS_NAME L"SampleWindow" 
#define WINDOW_TITLE L"Blaster Master"		
#define WINDOW_ICON_PATH L"BlasterMaster.ico" 

#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

#define MAX_FRAME_RATE 120

class Camera
{
public:
	HWND hWnd = 0;

	LPDIRECT3DTEXTURE9 texBrick;

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	int BackBufferWidth = 0;
	int BackBufferHeight = 0;

	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D images 

	Camera(HWND hWnd, LPDIRECT3DTEXTURE9 texBrick, LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddv,
		LPDIRECT3DSURFACE9 backBuffer, int BackBufferWidth, int BackBufferHeight, LPD3DXSPRITE spriteHandler);
	Camera() {}


	void DebugOutTitle(const wchar_t* fmt, ...);
	void DebugOut(const wchar_t* fmt, ...);

	HWND CreateCamera(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
	void InitDirectX();
	void LoadResources(Brick brick);
	void Render(Brick brick);
	int Run(Brick brick);
	void Cleanup();
};

