#include "Control.h"
Control::Control(int x, int y) : hWnd(0), x(x), y(y) {}
Button::Button(int x, int y, int width, int height, const wchar_t* text) : Control(x, y), width(width), height(height), txt(text) {}
Label::Label(int x, int y, const wchar_t* text) : Control(x, y), txt(text) {}
TextBox::TextBox(int x, int y, int width, int height, const wchar_t* defaultText) : Control(x, y), width(width), height(height), txt(defaultText) {}