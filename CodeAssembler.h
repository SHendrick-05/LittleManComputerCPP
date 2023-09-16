#pragma once
#include <map>
class Instruction
{
public:
	short opcode;
	short operand;
	const wchar_t* label;
};

//static std::map<const wchar_t*, short> opcodes;
static Instruction DecodeInstruction(const wchar_t*);