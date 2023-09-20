#include "Controls.h"

// All the text labels to be included
Label labels[] = {
	{270, 70, L"Program State"},
	{270, 135, L"Output"}
};

// All the buttons to be included.
Button buttons[] = {
	{270, 10, 250, 50, L"Run Code"} // Run button
};

// All the text boxes
TextBox textBoxes[] = {
	{10, 10, 250, 600, L"Type code here..."}, // Input
	{270, 100, 250, 25, L"state"}, // State
	{270, 150, 250, 460, L"out"} // Output
};

// The number of labels in the window
int labelCount = sizeof(labels) / sizeof(*labels);

// The number of buttons in the window
int buttonCount = sizeof(buttons) / sizeof(*buttons);

// The number of text boxes in the window.
int tBoxCount = sizeof(textBoxes) / sizeof(*textBoxes);