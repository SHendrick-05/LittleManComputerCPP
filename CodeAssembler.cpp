#include "CodeAssembler.h"
#include "framework.h"
#include <ranges>

static std::map<const wchar_t*, short> opcodes = {
	{L"LDA", 5}, // Load address into ACC
	{L"STA", 3}, // Store ACC in address
	{L"ADD", 1}, // Add address to ACC
	{L"SUB", 2}, // Subtract address from ACC
	{L"INP", 901}, // Take user input
	{L"OUT", 902}, // Output ACC
	{L"BRZ", 7}, // Branch if zero
	{L"BRP", 8}, // Branch if 0 or >0
	{L"BRA", 6}, // Branch
	{L"HLT", 0} // Stop
	// 10 = label
};

std::unique_ptr<Instruction> DecodeInstruction(wchar_t input[])
{
	// Return a null pointer if an empty instruction was given.
	if (input == L"")
	{
		return std::unique_ptr<Instruction>(nullptr);
	}

	// Init the instruction object.

	std::unique_ptr<Instruction> result(new Instruction());

	// Split the input into sections
	wchar_t* spliced[3];

	wchar_t* buffer;
	int len = wcslen(input);
	buffer = (wchar_t*)malloc(len);
	wchar_t* token = wcstok_s(input, L" ", &buffer);
	int i = 0;
	while (token)
	{
		spliced[i++] = token;
		token = wcstok_s(NULL, L" ", &buffer);
	}

	free(buffer);

	// Get opcode
	wchar_t* opcode = spliced[0];
	//TODO :Convert uppercase
	if (opcodes.count(opcode) != 0)
	{
		result->opcode = opcodes[opcode];
	}
	else
	{
		result->opcode = 10;
		result->label = opcode;
	}

	// Get appropriate labels if branch
	if (result->opcode > 5 && result->opcode < 9)
	{
		result->label = spliced[1];
	}

	// Get operand
	else if (sizeof(spliced) / sizeof(spliced[0]) != 1)
	{
		result->operand = _wtoi(spliced[1]);
	}
	
	return result;
}