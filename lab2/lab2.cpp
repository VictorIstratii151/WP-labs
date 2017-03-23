#include <windows.h>
#include "resource.h"


const char g_szClassName[] = "myWindowClass";
HWND g_hToolbar = NULL;
HWND Button1;


bool IsKeyPressed(UINT nVirtKey)
{
	return GetKeyState(nVirtKey) < 0 ? true : false;
}

void PaintBg(HWND hwnd) {

	PAINTSTRUCT ps;
	RECT r;
	static int a, b, c, textColor = 0;
	static bool bgFlag;

	GetClientRect(hwnd, &r);

	if (r.bottom == 0)
		return;

	HDC hdc = BeginPaint(hwnd, &ps);
	a = rand() % 255 + 1;
	b = rand() % 255 + 1;
	c = rand() % 255 + 1;
	bgFlag = true;
	if (bgFlag == true)
	{
		SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(a, b, c)));
	}
	InvalidateRect(hwnd, NULL, TRUE);

	EndPaint(hwnd, &ps);
}

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_PRESS:
			MessageBox(hwnd, "Hi!", "This is a message",
				MB_OK | MB_ICONEXCLAMATION);
			break;
		case IDC_OTHER:
			MessageBox(hwnd, "Bye!", "This is also a message",
				MB_OK | MB_ICONEXCLAMATION);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

int DisplayDialog()
{
	int msgboxID = MessageBox(
		NULL,
		"Do you like me?",
		"Hey",
		MB_ICONQUESTION | MB_YESNO
	);

	if (msgboxID == IDYES)
	{
		// TODO: add code
	}

	return msgboxID;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rcClient;
	HDC hdc;
	static HWND bgScrollBar;

	static int xPos, xMin, xMax;

	switch (msg)
	{
	case WM_CREATE:
	{
		HFONT hfDefault;
		HWND hEdit;

		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rcClient);
		int width = rcClient.right - rcClient.left;
		int height = rcClient.bottom - rcClient.top;
		Button1 = CreateWindowEx(NULL, "BUTTON", "Hi", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 3 * (width / 4), height / 4, 70, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);
		bgScrollBar = CreateWindowEx(NULL, "SCROLLBAR", "", WS_VISIBLE | WS_CHILD | SBS_HORZ, width / 2, 0, 220, 25, hwnd, (HMENU)IDC_BG_SCROLL, GetModuleHandle(NULL), NULL);
		EndPaint(hwnd, &ps);

		RegisterHotKey(hwnd, HK_CLOSE, MOD_CONTROL, 0x58);
		RegisterHotKey(hwnd, HK_MINIMIZE, MOD_CONTROL, 0x4D);
		RegisterHotKey(hwnd, HK_RESTORE, MOD_CONTROL, 0x52);

		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			0, 0, 100, 100, hwnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
		if (hEdit == NULL)
		{
			MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
		}

		hfDefault = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));

		xPos = 0;
		xMin = 0;
		xMax = 255;

		SetScrollRange(bgScrollBar, SB_CTL, xMin, xMax, FALSE);
		SetScrollPos(bgScrollBar, SB_CTL, xPos, TRUE);

		g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR),
			hwnd, ToolDlgProc);
		if (g_hToolbar != NULL)
		{
			ShowWindow(g_hToolbar, SW_SHOW);
		}
		else
		{
			MessageBox(hwnd, "CreateDialog returned NULL", "Warning!",
				MB_OK | MB_ICONINFORMATION);
		}
	}
	break;

	case WM_SIZE:
	{
		HWND hEdit;
		GetClientRect(hwnd, &rcClient);

		hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		SetWindowPos(hEdit, NULL, 0, 0, rcClient.right / 2, rcClient.bottom / 2, SWP_NOZORDER);
	}
	break;

	case WM_HSCROLL:
	{
		if ((HWND)lParam == bgScrollBar)
		{
			switch (LOWORD(wParam))
			{
				case SB_LINELEFT:
				{
					xPos -= 1;
					PaintBg(hwnd);
				}
				break;

				case SB_LINERIGHT:
				{
					xPos += 1;
					PaintBg(hwnd);
				}
				break;

				case SB_PAGELEFT:
				{
					xPos -= 10;
					PaintBg(hwnd);
				}
				break;

				case SB_PAGERIGHT:
				{
					xPos += 10;
					PaintBg(hwnd);
				}
				break;

				case SB_THUMBPOSITION:
				{
					PaintBg(hwnd);
				}
				break;

				case SB_TOP:
				{
					xPos = xMin;
					PaintBg(hwnd);
				}
				break;

				case SB_BOTTOM:
				{
					xPos = xMax;
					PaintBg(hwnd);
				}
				break;

				case SB_THUMBTRACK:
				{
					xPos = HIWORD(wParam);
					PaintBg(hwnd);
				}
				break;

				default:
					break;
			}

			SetScrollPos(bgScrollBar, SB_CTL, xPos, TRUE);
			if (xPos == xMax)
			{
				PaintBg(hwnd);
				EnableScrollBar(bgScrollBar, SB_CTL, ESB_DISABLE_RIGHT);
			}

			if (xPos == xMin)
			{
				PaintBg(hwnd);
				EnableScrollBar(bgScrollBar, SB_CTL, ESB_DISABLE_LEFT);
			}
		}
	}
	break;
	
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rcClient);
		int width = rcClient.right - rcClient.left;
		int height = rcClient.bottom - rcClient.top;
		MoveWindow(Button1, 3 * (width / 4), height / 4, 70, 30, TRUE);
		EndPaint(hwnd, &ps);

	}
	break;

	case WM_HOTKEY:
	{
		switch (wParam)
		{
			case HK_CLOSE:
			{
				PostQuitMessage(0);
			}
			break;

			case HK_MINIMIZE:
			{
				ShowWindow(hwnd, SW_MINIMIZE);
			}
			break;

			case HK_RESTORE:
			{
				ShowWindow(hwnd, SW_RESTORE);
			}
			break;

			default:
				break;
		}
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case IDC_BUTTON1:
			{
				DisplayDialog();
			}
			break;

			case ID_FILE_EXIT:
			{
				PostMessage(hwnd, WM_CLOSE, 0, 0);
			}
			break;

			case ID_DIALOG_SHOW:
			{
				ShowWindow(g_hToolbar, SW_SHOW);
			}
			break;

			case ID_DIALOG_HIDE:
			{
				ShowWindow(g_hToolbar, SW_HIDE);
			}
			break;
		}
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
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
	wc.hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_CURSOR));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);

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
		WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
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