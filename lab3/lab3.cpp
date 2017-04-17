
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

void initBezierVector(vector<POINT> &vect, int size, HWND hwnd)
{
	RECT rcClient;
	GetClientRect(hwnd, &rcClient);

	int width = rcClient.right - rcClient.left;
	int height = rcClient.bottom - rcClient.top;

	for (int i = 0; i < size; i++)
	{
		POINT currentElement;
		currentElement.x = rand() % width + 1;
		currentElement.y = rand() % height + 1;

		vect.push_back(currentElement);
	}
}

void MakeLines(HDC hdc, HWND hwnd, vector<ListItem> LinesVector)
{
	HPEN hPenOld;

	for (int i = 0; i < 5; i++)
	{
		ListItem currentElement = LinesVector[i];

		string xinfo2 = to_string(currentElement.xStart);
		const char * xinfo22 = xinfo2.c_str();

		COLORREF qLineColor = RGB(currentElement.properties.colorA, currentElement.properties.colorB, currentElement.properties.colorC);
		HPEN hLinePen = CreatePen(PS_SOLID, currentElement.properties.width, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		MoveToEx(hdc, currentElement.xStart, currentElement.yStart, NULL);
		LineTo(hdc, currentElement.xEnd, currentElement.yEnd);

		//MessageBoxA(hwnd, xinfo22, "in makelines", MB_OK);


		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);
	}
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

const char g_szClassName[] = "myWindowClass";
HWND Button1;
HWND Button2;

bool LineDraw = false;
BOOL willDraw = FALSE;
BOOL isDrawing = FALSE;

POINT coordinates[5];
POINT ptPrevious;
POINT ptCurrent;

vector<ListItem> LinesVector;
vector<vector<POINT>> arrOfBezierVectors;

COLORREF colour = RGB(0, 0, 0);

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rcClient;
	HDC hdc = NULL;
	HPEN hpen = NULL;

	

	switch (msg)
	{
	case WM_CREATE:
		{
			vector<ListItem> LinesVector;
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rcClient);

			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;
			Button1 = CreateWindowEx(NULL, "BUTTON", "Eraser", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 3 * (width / 4), height / 4, 70, 30, hwnd, (HMENU)IDC_ERASER, GetModuleHandle(NULL), NULL);
			Button2 = CreateWindowEx(NULL, "BUTTON", "Crayon", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 3 * (width / 4), height / 4 + 35, 70, 30, hwnd, (HMENU)IDC_CRAYON, GetModuleHandle(NULL), NULL);
			EndPaint(hwnd, &ps);
	}

	case WM_PAINT:
		{
			HPEN hPenOld;

			GetClientRect(hwnd, &rcClient);
			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;

			hdc = BeginPaint(hwnd, &ps);

			string sas = to_string(LinesVector.size());
			const char * sos = sas.c_str();


			if (LinesVector.size() == 5)
			{
				MakeLines(hdc, hwnd, LinesVector);
			}
			//string size = to_string(arrOfBezierVectors.size());
			//const char * csize = size.c_str();
			//MessageBoxA(hwnd, csize, "sas", MB_OK);

			if (arrOfBezierVectors.size() == 2)
			{
				/*vector<POINT> temp = arrOfBezierVectors[0];
				POINT * arr = &temp[0];

				string size = to_string(temp.size());
				const char * csize = size.c_str();
				MessageBoxA(hwnd, csize, "sas", MB_OK);*/

				for (vector <vector<POINT>> ::iterator it = arrOfBezierVectors.begin(); it != arrOfBezierVectors.end(); ++it)
				{
					vector<POINT> temp = *it;
					const int arrSize = temp.size();
					POINT * arr = new POINT[arrSize];

					for (int i = 0; i < temp.size(); i++)
					{
						arr[i] = temp[i];
					}

					/*for (int i = 0; i < temp.size(); i++)
					{
						string size = to_string(arr[i].x);
						const char * csize = size.c_str();
						MessageBoxA(hwnd, csize, "sas", MB_OK);
					}*/

					string size = to_string(sizeof(arr) / sizeof(arr[0]));
					const char * csize = size.c_str();
					//MessageBoxA(hwnd, csize, "sas", MB_OK);

					PolyBezierTo(hdc, arr, temp.size());
					MoveToEx(hdc, rand() % width + 1, rand() % height + 1, NULL);
				}


				//for (int i = 0; i < arrOfBezierVectors.size(); i++)
				//{
				//string size = to_string(arrOfBezierVectors.size());
				//const char * csize = size.c_str();
				//MessageBoxA(hwnd, csize, "sas", MB_OK);
				//	vector<POINT> temp = arrOfBezierVectors[i];
				//	POINT * arr = &temp[0];
				//	PolyBezierTo(hdc, arr, arrOfBezierVectors.size());
				//}
			}
			MoveWindow(Button1, 3 * (width / 4), height / 4, 70, 30, TRUE);
			MoveWindow(Button2, 3 * (width / 4), height / 4 + 35, 70, 30, TRUE);

			EndPaint(hwnd, &ps);
		}
	break;
	
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case ID_DRAW_ERASE:
				{
					LinesVector.clear();
					arrOfBezierVectors.clear();
					InvalidateRect(hwnd, NULL, TRUE);
				}
				break;

				case ID_DRAW_LINE:
				{
					GetClientRect(hwnd, &rcClient);

					int width = rcClient.right - rcClient.left;
					int height = rcClient.bottom - rcClient.top;

					LinesVector.clear();

					for (int i = 0; i < 5; i++)
					{
						ListItem item = initListItem(width, height);
						

						LinesVector.push_back(item);

						string xinfo1 = to_string(LinesVector[i].xStart);
						const char * xinfo11 = xinfo1.c_str();
						
					}
					InvalidateRect(hwnd, NULL, TRUE);
				}
				break;

				case ID_DRAW_PLANE:
				{
					InvalidateRect(hwnd, NULL, TRUE);
					drawFigures(hwnd);
				}
				break;

				case ID_DRAW_BEZIER:
				{
					arrOfBezierVectors.clear();

					int vectSize;
					for (int i = 0; i < 2; i++)
					{
						vector<POINT> bezierVector;
						vectSize = 3;
						initBezierVector(bezierVector, vectSize, hwnd);

						/*string size = to_string(bezierVector.size());
						const char * csize = size.c_str();
						MessageBoxA(hwnd, csize, "sas", MB_OK);*/

						InvalidateRect(hwnd, NULL, TRUE);

						arrOfBezierVectors.push_back(bezierVector);
					}
					vector<POINT> temp = arrOfBezierVectors[0];

					/*string size = to_string(temp.size());
					const char * csize = size.c_str();
					MessageBoxA(hwnd, csize, "sas", MB_OK);*/

					InvalidateRect(hwnd, NULL, TRUE);
				}
				break;

				case IDC_CRAYON:
				{
					colour = RGB(255, 0, 0);
					hpen = CreatePen(PS_SOLID, 5, colour);
					if (willDraw == TRUE)
					{
						willDraw = FALSE;
						isDrawing = FALSE;
					}
					else
					{
						willDraw = TRUE;
					}
					/*string size = to_string(willDraw);
					const char * csize = size.c_str();
					MessageBoxA(hwnd, csize, "sas", MB_OK);*/
				}
				break;

				case IDC_ERASER:
				{
					colour = RGB(255, 255, 255);
					hpen = CreatePen(PS_SOLID, 5, colour);
					//SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));

					if (willDraw == TRUE)
					{
						willDraw = FALSE;
						isDrawing = FALSE;
					}
					else
					{
						willDraw = TRUE;
					}
				}
				break;
			}
		}
	break;

	case WM_LBUTTONDOWN:
		{
			if (willDraw == TRUE)
			{
				hdc = GetDC(hwnd);

				/*colour = RGB(255, 0, 0);
				hpen = CreatePen(PS_SOLID, 5, colour);*/
				SelectObject(hdc, hpen);

				ptPrevious.x = LOWORD(lParam);
				ptPrevious.y = HIWORD(lParam);
				ptCurrent.x = LOWORD(lParam);
				ptCurrent.y = HIWORD(lParam);

				MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
				LineTo(hdc, ptPrevious.x, ptPrevious.y);

				isDrawing = TRUE;

				string size = to_string(willDraw);
				const char * csize = size.c_str();

				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
			}
		}
	break;

	case WM_LBUTTONUP:
		{
			hdc = GetDC(hwnd);
			if (isDrawing == TRUE)
			{
				ptCurrent.x = LOWORD(lParam);
				ptCurrent.y = HIWORD(lParam);

				MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
			}
			ReleaseDC(hwnd, hdc);
			isDrawing = FALSE;
		}
	break;

	case WM_MOUSEMOVE:
		{
			hdc = GetDC(hwnd);

			if (isDrawing == TRUE)
			{
				hpen = CreatePen(PS_SOLID, 5, colour);
				SelectObject(hdc, hpen);

				MoveToEx(hdc, ptCurrent.x, ptCurrent.y, NULL);
				ptCurrent.x = LOWORD(lParam);
				ptCurrent.y = HIWORD(lParam);
				LineTo(hdc, ptCurrent.x, ptCurrent.y);

			}

			DeleteObject(hpen);
			ReleaseDC(hwnd, hdc);
			/*if (willDraw == TRUE)
			{
				hdc = BeginPaint(hwnd, &ps);
				MoveToEx(hdc, ptPrevious.x, ptPrevious.y, NULL);
				LineTo(hdc, ptPrevious.x = LOWORD(lParam), ptPrevious.y = HIWORD(lParam));
				EndPaint(hwnd, &ps);
			}*/
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