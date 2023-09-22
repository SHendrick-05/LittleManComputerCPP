#pragma once
#include <windows.h>

struct Control {
	public:
		int x;
		int y;
		Control(int x, int y);
};

struct Button : public Control
{
public:
	const wchar_t* txt;
	int width;
	int height;
	Button(int, int, int, int, const wchar_t*);
};

struct Label : Control
{
	public:
		const wchar_t* txt;
		Label(int x, int y, const wchar_t* text);
};

struct TextBox : Control
{
	public:
		const wchar_t* txt;
		int width;
		int height;
		TextBox(int x, int y, int width, int height, const wchar_t* defaultText);
};