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
	UpdateState(L"EXECUTION FINISHED; PROGRAM HALTED.");

	// Return program to previous state
	ACC = 0;
	IAR = 0;
	HLT = false;
	codeLabels.clear();
	for (int i = 0; i < 1000; i++)
	{
		memory[i] = 0;
	}
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
		ACC = TakeInput();
		break;

		// TODO: OUT
	case 902:
	{
		wchar_t buffer[sizeof(int) * 8 + 1];
		swprintf(buffer, L"%d", GetValue(instr.operand));
		UpdateOutput(buffer);
		break;
	}

		// BRZ
	case 7:
		if (ACC == 0)
		{
			if (codeLabels.count(instr.label))
				IAR = codeLabels[instr.label];
			else throw 6;
		}
		break;

		// BRP
	case 8:
		if (ACC >= 0)
		{
			if (codeLabels.count(instr.label))
				IAR = codeLabels[instr.label];
			else throw 6;
		}
		break;

		// BRA
	case 6:
		if (codeLabels.count(instr.label))
			IAR = codeLabels[instr.label];
		else throw 6;
		break;

		// HLT
	case 0:
		HLT = true;
		break;
	}
}

static int TakeInput()
{
	UpdateState(L"AWAITING USER INPUT..");
	int inputID = MessageBox(
		NULL,
		L"User input required. Please enter a number.",
		L"LMC Input",
		MB_ICONASTERISK | MB_YESNO
	);
	return 0;
}

static int GetValue(short operand)
{
	return memory[operand];
}

