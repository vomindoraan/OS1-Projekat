#include "kernpcb.h"
#include "ivt.h"
#include "syscall.h"

Syscall* KernelPCB::syscallParams = NULL;

KernelPCB::KernelPCB(StackSize stackSize, Time timeSlice)
	: PCB(stackSize, timeSlice), state(READY)
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
