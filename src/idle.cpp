#include "idle.h"

IdlePCB::IdlePCB(StackSize stackSize, Time timeSlice)
	: PCB(stackSize, timeSlice)
{
	initializeStack(IdlePCB::idleWrapper);
}

void IdlePCB::idleWrapper()
{
	while (true) {
		// dispatch(); // TODO: Number of threads
	}
}
