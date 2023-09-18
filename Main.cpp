#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Control.h"
#include "Controls.h"


// Window class name
static TCHAR szWindowClass[] = _T("LMC");

// Title bar text
static TCHAR szTitle[] = _T("LMC");

// The Current instance
HINSTANCE hInst;

// The width of the window
const int windowWidth = 550;

// The height of the window
const int windowHeight = 660;

int test = 0;


// Forward declarations for functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitInstance(HINSTANCE, int);
ATOM RegisterWinClass(HINSTANCE);


int ButtonClick(HWND hWnd, HWND hButton)
{
	UpdateOutput(L"TEST");
}


// Entry point for the application
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) 
{
	

	// Attempt to register the class, and notify user if it failed.
	if (!RegisterWinClass(hInstance))
	{
		MessageBox(NULL, _T("RegisterClassEx call failed."), szTitle, NULL);
		return 1;
	}

	hInst = hInstance;

	// Attempt to create window, notify user if failed
	if (!InitInstance(hInstance, nCmdShow))
	{
		return 0;
	}

	// Main message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}


// Attempts to register a class
ATOM RegisterWinClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	return RegisterClassEx(&wcex);
}

//
// FUNCTION: InitInstance()
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	// Create the window.
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowWidth, windowHeight,
		NULL,
		NULL,
		hInst,
		NULL
	);

	// If there was an error creating the window.
	if (!hWnd)
	{
		return FALSE;
	}


	// Buttons.
	for (int i = 0; i < buttonCount; i++)
	{
		Button btn = buttons[i];
		btn.hWnd = CreateWindow(
			L"BUTTON",
			btn.txt,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			btn.x,
			btn.y,
			btn.width,
			btn.height,
			hWnd,
			NULL,
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL);
	}

	// TextBoxes
	for (int i = 0; i < tBoxCount; i++)
	{
		TextBox tBox = textBoxes[i];
		CreateWindow(
			L"EDIT",
			tBox.txt,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
			tBox.x,
			tBox.y,
			tBox.width,
			tBox.height,
			hWnd,
			NULL,
			NULL,
			NULL);
	}

	// Shows the window and makes it visible to the user.
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
// FUNCTION: WndProc()
// 
// PURPOSE: Handles messages sent to the window
// 
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
LRESULT CALLBACK WndProc(
	_In_ HWND hWnd, // Window handle
	_In_ UINT message, // The message being sent
	_In_ WPARAM wParam, // Additional message information
	_In_ LPARAM lParam // Additional message information
)
{
	
	HDC hdc; // Handle to Device Context
	TCHAR text[] = _T("Little Man Computer");

	switch (message)
	{
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			int wmCode = HIWORD(wParam);
			// Parse menu selections
			switch (wmId)
			{
			
			}
		}
		break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			// Perform drawing code here
			//swprintf_s(labels[0].txt, L"%d", test);

			// Title
			
			for (int i = 0; i < labelCount; i++)
			{
				Label lab = labels[i];
				TextOut(hdc, lab.x, lab.y, lab.txt, _tcslen(lab.txt));
			}

			//
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}

	return 0;
}

void UpdateOutput(const wchar_t* text)
{
	HWND outputHWND = textBoxes[2].hWnd;
	SendMessage(outputHWND, EM_SETSEL, WPARAM(0), LPARAM(-1));
	SendMessage(outputHWND, EM_REPLACESEL, WPARAM(TRUE), LPARAM(text));
}