#include <windows.h>
#include <vector>
#include "resource.h"
#include "objInfo.h"

using namespace std;

const char g_szClassName[] = "myWindowClass";


MovingObject * objects[1000];

int objectNumber = 0;
int tempNumber = 0;

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT rcClient;
	static HBITMAP hbmMEM;
	static HDC hdcMEM;
	static HDC hdc;
	static int timer_speed = 1;
	PAINTSTRUCT ps;

	srand(GetTickCount());

	switch (msg)
	{
		case WM_CREATE:
		{
			hdc = GetDC(hwnd);

			GetClientRect(hwnd, &rcClient);
			hdcMEM = CreateCompatibleDC(hdc);
			hbmMEM = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);
			SelectObject(hdcMEM, hbmMEM);

			ReleaseDC(hwnd, hdc);
			
			SetTimer(hwnd, ID_TIMER, timer_speed, NULL);

			RegisterHotKey(hwnd, HK_ADD, MOD_CONTROL, VK_UP);
			RegisterHotKey(hwnd, HK_DELETE, MOD_CONTROL, VK_DOWN);
		}
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rcClient);
			FillRect(hdcMEM, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

			for (int i = 0; i < objectNumber; i++)
			{
				objects[i]->move(hdcMEM, rcClient);
			}

			for (int i = 0; i < objectNumber - 1; i++)
			{
				for (int j = i + 1; j < objectNumber; j++)
				{
					interaction(*objects[i], *objects[j]);
				}
			}

			for (int i = 0; i < tempNumber; i++)
			{
				int R = rand() % 256;
				int G = rand() % 256;
				int B = rand() % 256;

				if (objects[i]->multiplied == 1)
				{
					POINT center2 = objects[i]->center;

					if (objects[i]->delta.x > 0 & objects[i]->delta.y < 0)
					{
						center2.x -= 50;
						center2.y -= 50;
					}
					else if (objects[i]->delta.x > 0 & objects[i]->delta.y > 0)
					{
						center2.x += 50;
						center2.y -= 50;
					}
					else if (objects[i]->delta.x < 0 & objects[i]->delta.y > 0)
					{
						center2.x += 50;
						center2.y += 50;
					}
					else if (objects[i]->delta.x < 0 & objects[i]->delta.y < 0)
					{
						center2.x -= 50;
						center2.y += 50;
					}

					POINT newSpeed;
					newSpeed.x = 1;
					newSpeed.y = 1;

					objects[objectNumber] = new MovingObject(center2, newSpeed, RGB(R, G, B), objectNumber);
					objects[objectNumber]->idHitObj = i;
					objects[objectNumber]->alterDirection(*objects[i]);
					objects[objectNumber]->multiplied = 3;
					objects[i]->multiplied = 3;
					objectNumber += 1;
				}
			}
			
			BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hdcMEM, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
		}
		break;

		case WM_TIMER:
		{
			InvalidateRect(hwnd, &rcClient, NULL);
		}
		break;

		case WM_HOTKEY:
		{
			switch(wParam)
			{
				case HK_ADD: // ctrl + up
				{

					static POINT coord;
					POINT initialSpeed;
					initialSpeed.x = 1;
					initialSpeed.y = 1;
					coord.x = LOWORD(lParam);
					coord.y = HIWORD(lParam);

					int R = rand() % 256;
					int G = rand() % 256;
					int B = rand() % 256;

					if (objectNumber == 20)
					{
						MessageBox(NULL, "Maximum number of objects on the screen!", "Epilepsy warning!",
							MB_ICONEXCLAMATION | MB_OK);
						return 0;
					}

					objects[objectNumber] = new MovingObject(coord, initialSpeed, RGB(R, G, B), objectNumber);
					objectNumber += 1;
					tempNumber = objectNumber;
				}
				break;

				case HK_DELETE: // ctrl + down
				{
					DestroyWindow(hwnd);
					PostQuitMessage(0);
				}

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
			DeleteObject(hbmMEM);
			DeleteDC(hdcMEM);
			KillTimer(hwnd, ID_TIMER);
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
