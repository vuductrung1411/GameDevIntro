#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include "Brick.h"
#include "Window.h"
#include "Camera.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window;

	window.hWnd = window.CreateNewWindow(hInstance, nCmdShow, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (window.hWnd == 0) return 0;

	window.InitDirectX();

	//--------------------------------------------------------------------------------------------------------------------

	Camera camera = Camera(Coords(0.0f, 0.0f), window.Height, window.Width);
	Brick* brick = new Brick();
	Brick* br = new Brick();

	br->coords.SetCoords(50.0f, 50.0f);
	//br->path = L"BlasterMaster.png";

	brick->SetStatus(STATUS_GO_AROUND_FOLLOW_CLOCKWISE);
	br->SetStatus(STATUS_GO_DOWN);

	brick->SetCamera(camera);
	br->SetCamera(camera);

	//--------------------------------------------------------------------------------------------------------------------

	window.LoadResources(*brick);
	window.LoadResources(*br);
	
	window.Run(*brick, *br);

	window.Cleanup();

	return 0;
}