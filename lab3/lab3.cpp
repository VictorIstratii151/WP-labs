#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"

const char g_szClassName[] = "myWindowClass";
HWND Button1;

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rcClient;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
		{
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rcClient);

			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;
			Button1 = CreateWindowEx(NULL, "BUTTON", "Hi", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 3 * (width / 4), height / 4, 70, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);
			
			EndPaint(hwnd, &ps);
	}

	case WM_PAINT:
		{
			srand(time(NULL));
			HPEN hPenOld;
			int a, b, c, textColor = 0;

			GetClientRect(hwnd, &rcClient);

			hdc = BeginPaint(hwnd, &ps);


			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;

			for (int i = 0; i < 5; i++)
			{
				a = rand() % 255 + 1;
				b = rand() % 255 + 1;
				c = rand() % 255 + 1;

				HPEN hLinePen;
				COLORREF qRandomColor = RGB(a, b, c);
				hLinePen = CreatePen(PS_SOLID, rand() % 20 + 1, qRandomColor);
				hPenOld = (HPEN)SelectObject(hdc, hLinePen);

				MoveToEx(hdc, rand() % width, rand() % height, NULL);
				LineTo(hdc, rand() % width, rand() % height);

				SelectObject(hdc, hPenOld);
				DeleteObject(hLinePen);
			}

		/*//Draw a red line
		HPEN hLinePenRed;
		COLORREF qLineColorRed = RGB(255, 0, 0);
		hLinePenRed = CreatePen(PS_SOLID, 7, qLineColorRed);
		hPenOld = (HPEN)SelectObject(hdc, hLinePenRed);

		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 500, 250);

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePenRed);

		//Draw a green line line
		HPEN hLinePenGreen;
		COLORREF qLineColorGreen = RGB(0, 255, 0);
		hLinePenGreen = CreatePen(PS_SOLID, 17, qLineColorGreen);
		hPenOld = (HPEN)SelectObject(hdc, hLinePenGreen);

		MoveToEx(hdc, 150, 10050, NULL);
		LineTo(hdc, 600, 200);

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePenGreen);*/

		//Draw a blue ellipse
			HPEN hEllipsePen;
			COLORREF qEllipseColor = RGB(0, 0, 255);
			hEllipsePen = CreatePen(PS_DOT, 1, qEllipseColor);
			hPenOld = (HPEN)SelectObject(hdc, hEllipsePen);

			Arc(hdc, 100, 100, 500, 250, 0, 0, 0, 0);

			SelectObject(hdc, hPenOld);
			DeleteObject(hEllipsePen);

			EndPaint(hwnd, &ps);
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
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
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