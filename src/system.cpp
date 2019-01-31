#include "system.h"
#include "ivt.h"

PCB*       System::runningPCB;
PCB*       System::mainPCB;
KernelPCB* System::kernelPCB;
IdlePCB*   System::idlePCB;
SleepList* System::sleepList;

void System::start()
{
	mainPCB = new PCB(0, defaultTimeSlice);
	mainPCB->state(PCB::RUNNING);
	runningPCB = mainPCB;

	kernelPCB = new KernelPCB(0x400UL, 0U);
	// kernelPCB->reschedule();

	idlePCB = new IdlePCB(0x400UL, 1U);
	idlePCB->reschedule();

	sleepList = new SleepList();

	initializeInterrupts();
}

void System::finish()
{
	restoreInterrupts();

	delete mainPCB;
	delete kernelPCB;
	delete idlePCB;
	delete sleepList;
}

void System::syscall(Syscall* params)
{
	// TODO
}
