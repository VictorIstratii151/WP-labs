#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"

void drawLines(HWND hwnd)
{
	srand(time(NULL));

	PAINTSTRUCT ps;
	RECT rcClient;
	HPEN hPenOld;
	HDC hdc; 

	static int a, b, c;

	hdc = BeginPaint(hwnd, &ps);

	GetClientRect(hwnd, &rcClient);

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

		int xStart = rand() % width;
		int yStart = rand() % height;
		int xEnd = rand() % width;
		int yEnd = rand() % height;



		MoveToEx(hdc, xStart, yStart, NULL);
		LineTo(hdc, xEnd, yEnd);

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);
	}

	EndPaint(hwnd, &ps);
}

const char g_szClassName[] = "myWindowClass";
HWND Button1;
bool LineDraw = false;
POINT coordinates[5];

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
			Button1 = CreateWindowEx(NULL, "BUTTON", "Erase", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 3 * (width / 4), height / 4, 70, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);
			
			EndPaint(hwnd, &ps);
	}

	case WM_PAINT:
		{
			HPEN hPenOld;
			srand(time(NULL));
			int a, b, c = 0;

			GetClientRect(hwnd, &rcClient);

			hdc = BeginPaint(hwnd, &ps);


			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;

			MoveWindow(Button1, 3 * (width / 4), height / 4, 70, 30, TRUE);

		

			/*if (LineDraw == true) {
				for (int i = 0; i < 5; i++)
				{
					a = rand() % 255 + 1;
					b = rand() % 255 + 1;
					c = rand() % 255 + 1;

					HPEN hLinePen;
					COLORREF qRandomColor = RGB(a, b, c);
					hLinePen = CreatePen(PS_SOLID, rand() % 20 + 1, qRandomColor);
					hPenOld = (HPEN)SelectObject(hdc, hLinePen);

					int xStart = rand() % width;
					int yStart = rand() % height;
					int xEnd = rand() % width;
					int yEnd = rand() % height;

					

					MoveToEx(hdc, xStart, yStart, NULL);
					LineTo(hdc, xEnd, yEnd);

					SelectObject(hdc, hPenOld);
					DeleteObject(hLinePen);
				}
				LineDraw = false;
			}*/

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
	
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case ID_DRAW_ERASE:
				{
					GetClientRect(hwnd, &rcClient);
					InvalidateRect(hwnd, NULL, TRUE);
					//RedrawWindow(hwnd, &rcClient, NULL, RDW_ERASE);
				}
				break;

				case ID_DRAW_LINE:
				{
					InvalidateRect(hwnd, NULL, TRUE);
					drawLines(hwnd);
				}
				break;
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);;
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