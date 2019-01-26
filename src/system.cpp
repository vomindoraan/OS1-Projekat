#include "system.h"
#include "ivt.h"

PCB*       System::runningPCB;
PCB*       System::mainPCB;
KernelPCB* System::kernelPCB;
IdlePCB*   System::idlePCB;
SleepList* System::sleepList;

void System::start()
{
	System::mainPCB    = new PCB(0, defaultTimeSlice);
	System::mainPCB->state(PCB::RUNNING);
	System::runningPCB = mainPCB;
	System::kernelPCB  = new KernelPCB(0x400UL, 0U);
	System::idlePCB    = new IdlePCB  (0x400UL, 1U);
	System::sleepList  = new SleepList();

	initializeInterrupts();
}

void System::finish()
{
	restoreInterrupts();

	delete System::mainPCB;
	delete System::kernelPCB;
	delete System::idlePCB;
	delete System::sleepList;
}
