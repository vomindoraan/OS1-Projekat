#include "locks.h"
#include "idle.h"
#include "ivt.h"
#include "pcb.h"
#include <iostream.h>

int userMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	HARD_LOCKED(cout << "Start" << endl);

	// Create PCB for the main function
	PCB* mainPCB = new PCB(0, defaultTimeSlice);
	mainPCB->state(PCB::RUNNING);
	PCB::running = mainPCB;

	Idle::instance(); // Create idle PCB

	initIVT();

	HARD_LOCKED(cout << "Test" << endl);

	restoreIVT();

	HARD_LOCKED(cout << "Finish" << endl);
	return 0;
}
