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



class Window
{
public:
	HWND hWnd = 0;

	LPDIRECT3DTEXTURE9 texBrick;

	LPDIRECT3D9 d3d = NULL;						
	LPDIRECT3DDEVICE9 d3ddv = NULL;				

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	int Width, Height;
	float x, y;

	LPD3DXSPRITE spriteHandler = NULL;			

	Window(HWND hWnd, LPDIRECT3DTEXTURE9 texBrick, LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddv,
		LPDIRECT3DSURFACE9 backBuffer, int Width, int Height, LPD3DXSPRITE spriteHandler);
	Window() {}

	void SetCoordAndSize(float x, float y, int Width, int Height);

	void DebugOutTitle(const wchar_t* fmt, ...);
	void DebugOut(const wchar_t* fmt, ...);

	HWND CreateNewWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
	void InitDirectX();
	void LoadResources(Brick brick);
	void Render(Brick brick, Brick br);
	int Run(Brick brick, Brick br);
	void Cleanup();
};

