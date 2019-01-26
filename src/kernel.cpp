#include "kernel.h"

KernelPCB::KernelPCB(StackSize stackSize, Time timeSlice)
	: PCB(stackSize, timeSlice)
{
	initializeStack(KernelPCB::syscallWrapper);
}

void KernelPCB::syscallWrapper()
{
	// TODO
}
