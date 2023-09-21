#pragma once
#include <memory>
#include <map>

class Instruction
{
public:
	short opcode;
	short operand;
	wchar_t* label;
};

//static std::map<const wchar_t*, short> opcodes;
static std::unique_ptr<Instruction> DecodeInstruction(wchar_t[]);