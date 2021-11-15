#include "Camera.h"


Camera::Camera(HWND hWnd, LPDIRECT3DTEXTURE9 texBrick, LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddv,
	LPDIRECT3DSURFACE9 backBuffer, int BackBufferWidth, int BackBufferHeight, LPD3DXSPRITE spriteHandler)
{
	this->hWnd = hWnd;
	this->texBrick = texBrick;
	this->d3d = d3d;
	this->d3ddv = d3ddv;
	this->backBuffer = backBuffer;
	this->BackBufferWidth = BackBufferWidth;
	this->BackBufferHeight = BackBufferHeight;
	this->spriteHandler = spriteHandler;
}





LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// DEBUG SUPPORT FUNCTIONS //////////////
#define _W(x)  __W(x)
#define __W(x)  L##x

#define VA_PRINTS(s) {				\
		va_list argp;				\
		va_start(argp, fmt);		\
		vswprintf_s(s, fmt, argp);	\
		va_end(argp);				\
}		

void Camera::DebugOut(const wchar_t* fmt, ...)
{
	wchar_t s[4096];
	VA_PRINTS(s);
	OutputDebugString(s);
}

void Camera::DebugOutTitle(const wchar_t* fmt, ...)
{
	wchar_t s[1024];
	VA_PRINTS(s);
	SetWindowText(hWnd, s);
}
//////////////////////////////////////////

void Camera::InitDirectX()
{
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	// retrieve window width & height so that we can create backbuffer height & width accordingly 
	RECT r;
	GetClientRect(this->hWnd, &r);

	this->BackBufferWidth = r.right + 1;
	this->BackBufferHeight = r.bottom + 1;

	d3dpp.BackBufferHeight = this->BackBufferHeight;
	d3dpp.BackBufferWidth = this->BackBufferWidth;

	this->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,			// use default video card in the system, some systems have more than one video cards
		D3DDEVTYPE_HAL,				// HAL = Hardware Abstraction Layer - a "thin" software layer to allow application to directly interact with video card hardware
		this->hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->d3ddv);

	if (this->d3ddv == NULL)
	{
		DebugOut(L"[ERROR] CreateDevice failed\n %s %d", __FILE__, __LINE__);
		return;
	}

	this->d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &this->backBuffer);

	// Initialize Direct3DX helper library
	D3DXCreateSprite(this->d3ddv, &this->spriteHandler);

	DebugOut(L"[INFO] InitDirectX OK\n");
}

void Camera::LoadResources(Brick brick)
{
	HRESULT result = D3DXCreateTextureFromFileEx(
		this->d3ddv,								// Pointer to Direct3D device object
		brick.path,							// Path to the image to load
		D3DX_DEFAULT_NONPOW2, 				// Auto texture width (get from file)
		D3DX_DEFAULT_NONPOW2, 				// Auto texture height (get from file)
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),		// Transparent color
		NULL,
		NULL,
		&this->texBrick);

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] CreateTextureFromFileEx %s failed\n", brick.path /*BRICK_TEXTURE_PATH*/);
		return;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", brick.path  /*BRICK_TEXTURE_PATH*/);
}

void Camera::Render(Brick brick, Brick br)
{
	if (this->d3ddv->BeginScene())
	{
		// Clear the whole window with a color
		this->d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXVECTOR3 p(brick.x, brick.y, 0);
		this->spriteHandler->Draw(texBrick, NULL, NULL, &p, D3DCOLOR_WHITE);

		D3DXVECTOR3 p2(br.x, br.y, 0);
		this->spriteHandler->Draw(texBrick, NULL, NULL, &p2, D3DCOLOR_WHITE);

		DebugOutTitle(L"%s (%0.1f,%0.1f) v:%0.1f", WINDOW_TITLE, brick.x, brick.y, brick.vx);

		spriteHandler->End();
		this->d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	this->d3ddv->Present(NULL, NULL, NULL, NULL);
}

int Camera::Run(Brick brick, Brick br)
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			brick.Update(0.0f, 0.0f, this->BackBufferHeight, this->BackBufferWidth, dt);
			br.Update(0.0f, 0.0f, this->BackBufferHeight, this->BackBufferWidth, dt);
			Render(brick, br);
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

HWND Camera::CreateCamera(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	//Try this to see how the debug function prints out file and line 
	//wc.hInstance = (HINSTANCE)-100; 

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

void Camera::Cleanup()
{
	this->texBrick->Release();
	this->spriteHandler->Release();
	this->backBuffer->Release();
	this->d3ddv->Release();
	this->d3d->Release();

	DebugOut(L"[INFO] Cleanup Ok\n");
}


