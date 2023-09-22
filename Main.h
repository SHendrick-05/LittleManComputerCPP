#pragma once
#include <windows.h>

extern HWND hOut;
extern HWND hState;
extern void UpdateOutput(const wchar_t*);
extern void ClearOutput();
extern void UpdateState(const wchar_t* text);