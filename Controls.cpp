#include "Controls.h"

// All the text labels to be included
Label labels[] = {
	{270, 70, L"Program State"},
	{270, 135, L"Output"}
};

// All the buttons to be included.
Button buttons[] = {
	{270, 10, 250, 50, L"Run Code"}
};

// All the text boxes
TextBox textBoxes[] = {
	{10, 10, 250, 600, L"Type code here..."},
	{270, 100, 250, 25, L""}, // State
	{270, 150, 250, 460, L""} // Output
};

int labelCount = sizeof(labels)/sizeof(*labels);
int buttonCount = sizeof(buttons)/sizeof(*buttons);
int tBoxCount = sizeof(textBoxes)/sizeof(*textBoxes);