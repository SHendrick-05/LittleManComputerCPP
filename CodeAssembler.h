#include <map>
#pragma once
class Instruction
{
public:
	short opcode;
	const wchar_t* operand;
	const wchar_t* label;
};

static std::map<const wchar_t*, short> opcodes;
static Instruction DecodeInstruction(const wchar_t*);