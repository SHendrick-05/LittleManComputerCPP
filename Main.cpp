#include "framework.h"
#include "resource.h"
#include "Control.h"
#include "Controls.h"
#include "CodeAssembler.h"
#include "CodeHandler.h"
#include "Main.h"


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

HWND hIn;
HWND hOut;
HWND hState;


// Forward declarations for functions

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitInstance(HINSTANCE, int);
ATOM RegisterWinClass(HINSTANCE);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);



int ButtonClick(HWND hWnd, HWND hButton)
{
	// Clear the output
	ClearOutput();


	// Reserve memory and get the text.
	int len = GetWindowTextLength(hIn);
	auto buff = (LPWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(len + 1), MEM_COMMIT, PAGE_READWRITE);
	GetWindowText(hIn, buff, len + 1);

	MessageBox(NULL, buff, L"Test", MB_ICONASTERISK | MB_YESNO);

	// Get a vector of lines.
	std::vector<wchar_t*> lines;
	std::vector<Instruction> instrList;
	wchar_t* tok;
	wchar_t* tokstate = (wchar_t*)malloc(sizeof(wchar_t*) * 10);
	// Get first line 
	tok = wcstok_s(buff, L"\r\n", &tokstate);

	// Loop through the rest of the lines.
	while (tok != NULL)
	{
		// Add the previous line to the list
		lines.push_back(tok);
		// Get the next line.
		tok = wcstok_s(NULL, L"\r\n", &tokstate);
	}

	for (wchar_t* line : lines)
	{
		std::unique_ptr<Instruction> decInstr = DecodeInstruction(line);
		if (decInstr != nullptr)
		{
			instrList.push_back(*decInstr);
		}
	}

	// Assign the CodeHandler.h instruction list
	InstrList = instrList;
	// Run the program.
	StartExecution();

	// Free the memory



	return 1;
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
		CreateWindow(
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
		HWND tHwnd = CreateWindow(
			L"EDIT",
			tBox.txt,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
			tBox.x,
			tBox.y,
			tBox.width,
			tBox.height,
			hWnd,
			NULL,
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL);
		
		
		// Set HWND variables.
		switch (i)
		{
		case 0:
			hIn = tHwnd;
			break;
		case 1:
			hState = tHwnd;
			break;
		case 2:
			hOut = tHwnd;
			break;
		}
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
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				if (wmCode == BN_CLICKED) {
					if (ButtonClick(hWnd, (HWND)lParam))
						break;
				}
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			// Perform drawing code here

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


// Message handler for About box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//
// FUNCTION: UpdateOutput()
//
// PURPOSE: Appends text to the output Edit control.
void UpdateOutput(const wchar_t* text)
{
	int index = GetWindowTextLength(hOut);
	SendMessage(hOut, EM_SETSEL, WPARAM(index), LPARAM(index));
	SendMessage(hOut, EM_REPLACESEL, WPARAM(0), LPARAM(text));
}

// 
// FUNCTION: ClearOutput()
// 
// PURPOSE: Replaces the output edit control's text with an empty string.
void ClearOutput()
{
	SendMessage(hOut, WM_SETTEXT, WPARAM(0), LPARAM(L""));
}

void UpdateState(const wchar_t* text)
{
	SendMessage(hState, WM_SETTEXT, WPARAM(0), LPARAM(text));
}