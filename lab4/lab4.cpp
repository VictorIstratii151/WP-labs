#include <windows.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";

typedef struct _BALLINFO
{
	int width;
	int height;
	int x;
	int y;

	int dx;
	int dy;
}BALLINFO;

typedef struct __BALL
{
	BALLINFO g_ballInfo;
	HBITMAP g_hbmBall;
	HBITMAP g_hbmMask;
}BALL;

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT rcClient;
	static HBITMAP hbmMEM;
	static HDC hdcMEM;
	static HDC hdc;
	static int timer_speed = 1;
	switch (msg)
	{
		case WM_CREATE:
		{
			hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rcClient);
			hdcMEM = CreateCompatibleDC(hdc);
			hbmMEM = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);
			SelectObject(hdcMEM, hbmMEM);
			
			SetTimer(hwnd, ID_TIMER, timer_speed, NULL);

			RegisterHotKey(hwnd, HK_ADD, MOD_CONTROL, VK_UP);

		}
		break;

		case WM_HOTKEY:
		{
			switch(wParam)
			{
				case HK_ADD:
				{

				}
				break;

				default:
				{
					break;
				}
			}
		}
		break;

		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
