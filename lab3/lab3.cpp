#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <list>
#include <vector>
//#include <gdiplus.h>
#include "resource.h"
#include "listStuff.h"
#include <string>

using namespace std;
//using namespace Gdiplus;
//#pragma comment (lib, "Gdiplus.lib")

void MakeLines(HDC hdc, vector<ListItem> LinesVector)
{
	HPEN hPenOld;

	for (int i = 0; i < LinesVector.size(); i++)
	{
		ListItem currentElement = LinesVector[i];

		COLORREF qLineColor = RGB(currentElement.properties.colorA, currentElement.properties.colorB, currentElement.properties.colorC);
		HPEN hLinePen = CreatePen(PS_SOLID, currentElement.properties.width, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		MoveToEx(hdc, currentElement.xStart, currentElement.yStart, NULL);
		LineTo(hdc, currentElement.xEnd, currentElement.yEnd);

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);
	}

	// Draw a red line
	/*HPEN hLinePen;
	COLORREF qLineColor;
	qLineColor = RGB(255, 0, 0);
	hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);

	MoveToEx(hdc, 100, 100, NULL);
	LineTo(hdc, 500, 250);

	SelectObject(hdc, hPenOld);
	DeleteObject(hLinePen);*/
	//USE GDI +
}

void drawFigures(HWND hwnd)
{
	srand(time(NULL));

	PAINTSTRUCT ps;
	RECT rcClient;
	HPEN hPenOld;
	HDC hdc;

	static int a, b, c;

	hdc = BeginPaint(hwnd, &ps);

	GetClientRect(hwnd, &rcClient);
	
	POINT arrow[7];
	arrow[0].x = 20;
	arrow[0].y = 50;
	arrow[1].x = 180;
	arrow[1].y = 50;
	arrow[2].x = 180;
	arrow[2].y = 20;
	arrow[3].x = 230;
	arrow[3].y = 70;
	arrow[4].x = 180;
	arrow[4].y = 120;
	arrow[5].x = 180;
	arrow[5].y = 90;
	arrow[6].x = 20;
	arrow[6].y = 90;

	POINT triangle[3];
	triangle[0].x = 200;
	triangle[0].y = 200;
	triangle[1].x = 270;
	triangle[1].y = 240;
	triangle[2].x = 230;
	triangle[2].y = 110;

	Polygon(hdc, arrow, 7);
	Polygon(hdc, triangle, 3);

	HPEN hEllipsePen;
	COLORREF qEllipseColor = RGB(0, 0, 255);
	hEllipsePen = CreatePen(PS_DOT, 1, qEllipseColor);
	hPenOld = (HPEN)SelectObject(hdc, hEllipsePen);

	Arc(hdc, 100, 100, 500, 250, 0, 0, 0, 0);

	SelectObject(hdc, hPenOld);
	DeleteObject(hEllipsePen);

	HPEN hRoundRectPen;
	COLORREF qRoundRectColor = RGB(123, 54, 100);
	hRoundRectPen = CreatePen(PS_SOLID, 10, qRoundRectColor);
	hPenOld = (HPEN)SelectObject(hdc, hRoundRectPen);

	RoundRect(hdc, 150, 150, 200, 200, 42, 38);

	SelectObject(hdc, hPenOld);
	DeleteObject(hRoundRectPen);

	EndPaint(hwnd, &ps);
}

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
vector<ListItem> LinesVector;

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
			vector<ListItem> LinesVector;
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

			GetClientRect(hwnd, &rcClient);
			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;

			hdc = BeginPaint(hwnd, &ps);

			string sas = to_string(LinesVector.size());
			const char * sos = sas.c_str();

			//MessageBoxA(hwnd, sos, "sas", MB_OK);

			if (LinesVector.size() != 0)
			{
				MakeLines(hdc, LinesVector);
			}

			MoveWindow(Button1, 3 * (width / 4), height / 4, 70, 30, TRUE);

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
				}
				break;

				case ID_DRAW_LINE:
				{
					GetClientRect(hwnd, &rcClient);

					int width = rcClient.right - rcClient.left;
					int height = rcClient.bottom - rcClient.top;

					if (LinesVector.size() != 0)
					{
						LinesVector.clear();
					}
					for (int i = 0; i < 5; i++)
					{
						ListItem item = initListItem(width, height);
						

						LinesVector.push_back(item);

						string sas = to_string(LinesVector.size());
						const char * sos = sas.c_str();

						MessageBoxA(hwnd, sos, "in wm_lines", MB_OK);
					}
					InvalidateRect(hwnd, NULL, TRUE);
					//drawLines(hwnd);
				}
				break;

				case ID_DRAW_PLANE:
				{
					InvalidateRect(hwnd, NULL, TRUE);
					drawFigures(hwnd);
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