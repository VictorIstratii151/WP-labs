#include <windows.h>
#include <stdlib.h>

#define IDC_BUTTON1 1
#define IDC_BUTTON2 2

const char g_szClassName[] = "myWindowClass";
HFONT g_hfFont = NULL;
BOOL g_bOpaque = TRUE;
COLORREF g_rgbText = RGB(255, 0, 0);
COLORREF g_rgbBackground = RGB(0, 0, 255);
COLORREF bg;

void changeBg(HWND hwnd)
{
	bg = 0x00FF00FF;
	InvalidateRect(hwnd, NULL, TRUE);
}


void DrawClientMessage(HDC hdc, RECT* prc, HFONT hf)
{
	char Sentence[] = "Random sentence on the screen.";
	char simpleSentence[] = "Regular sentence";
	char szTitle[] = "Done with Pride and Prejudice by Victor Istratii.";
	HFONT hfOld = (HFONT)SelectObject(hdc, hf);
	DrawText(hdc, szTitle, -1, prc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	DrawText(hdc, simpleSentence, -1, prc, DT_WORDBREAK | DT_VCENTER | DT_CENTER);
	SetBkColor(hdc, g_rgbBackground);
	SetTextColor(hdc, g_rgbText);
	DrawText(hdc, Sentence, -1, prc, DT_WORDBREAK);
	SelectObject(hdc, hfOld);
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND blueButton, pressMe;
	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
	LPDRAWITEMSTRUCT pdis;
	RECT rcClient;
	PAINTSTRUCT ps;
	HDC hdc;
	HFONT g_hfFont = NULL;
	switch (msg)
	{
		case WM_CREATE:
		{
			g_hfFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			GetClientRect(hwnd, &rcClient);
			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;
			pressMe = CreateWindowEx(NULL, "BUTTON", "Press me!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				width/ 2, height / 5, 75, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);

			blueButton = CreateWindowEx(NULL, "BUTTON", "Don't press me!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				width / 4, height / 5, 120, 30, hwnd, (HMENU)IDC_BUTTON2, GetModuleHandle(NULL), NULL);
				//(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

			HGDIOBJ defaultFont = GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(pressMe, WM_SETFONT, (WPARAM)defaultFont, MAKELPARAM(FALSE, 0));
		}
		break;

		case WM_ERASEBKGND:
		{
			HPEN pen;
			HBRUSH brush;
			RECT rect;

			pen = CreatePen(PS_SOLID, 1, bg);
			brush = CreateSolidBrush(bg);
			SelectObject((HDC)wParam, pen);
			SelectObject((HDC)wParam, brush);

			GetClientRect(hwnd, &rect);

			Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);
		}
		break;
		
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1:
				{
					MessageBox(hwnd, "Thanks for clicking!", "Button clicked.", MB_OK | MB_ICONINFORMATION);
				}
				break;

				case IDC_BUTTON2:
				{
					MessageBox(hwnd, "I TOLD YOU NOT TO CLICK!!1", "WHY WOULD YOU DO THIS?!", MB_OK | MB_ICONINFORMATION);
				}
				break;
			}
		}

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_MAXIMIZE:
				{
					GetClientRect(hwnd, &rcClient);
					int width = rcClient.right - rcClient.left;
					int height = rcClient.bottom - rcClient.top;
					HWND SAS = CreateWindowEx(NULL, "BUTTON", "Geeez!!", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						rand() % (width + 1 - 0) + 0, rand() % (height + 1 - 0) + 0, 75, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);
				}
				break;

			case SC_MINIMIZE:
				{
					HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
					SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
					changeBg(hwnd);
				}
				break;

			default:
				{
					return DefWindowProc(hwnd, msg, wParam, lParam);
				}
			}
		}
		break;

		case WM_CLOSE:
		{
			/*GetClientRect(hwnd, &rcClient);
			int width = rcClient.right - rcClient.left;
			int height = rcClient.bottom - rcClient.top;
			MoveWindow(hwnd, 50, 120, width, height, TRUE);*/
			DestroyWindow(hwnd);
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rcClient);

			DrawClientMessage(hdc, &rcClient, g_hfFont);

			EndPaint(hwnd, &ps);
		}
		break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
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
	wc.style = CS_VREDRAW | CS_HREDRAW;
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