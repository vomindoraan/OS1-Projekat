#include "kernel.h"
#include "ivt.h"
#include "syscall.h"
#include <stdlib.h>

Syscall* KernelPCB::syscallParams = NULL;

KernelPCB::KernelPCB(StackSize stackSize, Time timeSlice)
	: PCB(stackSize, timeSlice)
{
	initializeStack(syscallWrapper);
}

void KernelPCB::syscallWrapper()
{
	if (!syscallParams) return;

	switch ((Syscall::Operation) syscallParams->params[0]) {
		// TODO
	}

	asm int IVTNO_SYSCALL_EXIT;
}
