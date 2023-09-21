#include "CodeHandler.h"
#include "Main.cpp"

static void StartExecution()
{
	ClearOutput();

	// Loop over all the labels.
	for (auto& instr : InstrList)
	{
		// Disregard if it is an actual opcode.
		if (instr.opcode != 10)
			continue;
		// If label not in list, add it.
		auto it = std::find(InstrList.begin(), InstrList.end(), instr);
		auto index = std::distance(InstrList.begin(), it);
		codeLabels.emplace(instr.label, index);
	}

	// Run instructions
	while (!HLT)
	{
		RunInstruction();
	}
	updatesta
}

static void RunInstruction()
{
	if (IAR >= InstrList.size())
	{
		HLT = true;
		return;
	}
	Instruction instr = InstrList[IAR];
	
	switch (instr.opcode)
	{
		// LDA
	case 5:
		ACC = GetValue(instr.operand);
		break;
		// STA
	case 3:
		memory[instr.operand] = ACC;
		break;
		// ADD
	case 1:
		ACC += GetValue(instr.operand);
		break;
		// SUB
	case 2:
		ACC -= GetValue(instr.operand);
		break;
		// TODO: INP
	case 901:
		int value = GetValue(instr.operand);
		wchar_t buffer[sizeof(int) * 8 + 1];
		swprintf(buffer, L"%d", value);
		UpdateOutput(buffer);
		break;
		// TODO: OUT
	case 902:
		break;
		// BRZ
	case 7:
		break;
		// BRP
	case 8:
		break;
		// BRA
	case 6:
		
		break;
		// HLT
	case 0:
		HLT = true;
		break;
	}
}

static int TakeInput()
{
	return 0;
}

static int GetValue(short operand)
{
	return memory[operand];
}

