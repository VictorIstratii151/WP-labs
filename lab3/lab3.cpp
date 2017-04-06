#include <windows.h>

const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rcClient;
	HDC hdc;

	switch (msg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		HPEN hPenOld;

		//Draw a red line
		HPEN hLinePen;
		COLORREF qLineColor = RGB(255, 0, 0);
		hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 500, 250);

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);

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