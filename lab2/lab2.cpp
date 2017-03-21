#include <windows.h>

#define IDC_BUTTON1 1


const char g_szClassName[] = "myWindowClass";
HWND Button1;


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

	switch (msg)
	{
	case WM_CREATE:
	{
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rcClient);
		int width = rcClient.right - rcClient.left;
		int height = rcClient.bottom - rcClient.top;
		Button1 = CreateWindowEx(NULL, "BUTTON", "Hi", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, width / 4, height / 4, 70, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);
		EndPaint(hwnd, &ps);
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
		MoveWindow(Button1, width / 4, height / 4, 70, 30, TRUE);
		EndPaint(hwnd, &ps);

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
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
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