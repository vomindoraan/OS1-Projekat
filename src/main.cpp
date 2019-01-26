#include "locks.h"
#include "idle.h"
#include "ivt.h"
#include "pcb.h"
#include "sleeplst.h"
#include <iostream.h>

PCB*       mainPCB   = new PCB(0, defaultTimeSlice);
IdlePCB*   idlePCB   = new IdlePCB(0x400UL, 1U);
SleepList* sleepList = new SleepList();

int userMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	HARD_LOCKED(cout << "Start" << endl);

	// Set main function PCB
	mainPCB->state(PCB::RUNNING);
	PCB::running = mainPCB;

	initializeInterrupts();

	HARD_LOCKED(cout << "User" << endl);
	int ret = userMain(argc, argv);

	restoreInterrupts();

	HARD_LOCKED(cout << "Finish" << endl);

	delete mainPCB;
	delete idlePCB;
	delete sleepList;

	return ret;
}
