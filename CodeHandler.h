#pragma once
#include <map>
#include <vector>
#include "CodeAssembler.h"
static int memory[1000];
static std::map<wchar_t*, int> codeLabels;
static std::vector<Instruction> InstrList;
static int ACC;
static int IAR;
static bool HLT;

void StartExecution();
static void RunInstruction();
static int TakeInput();
static int GetValue(short);
