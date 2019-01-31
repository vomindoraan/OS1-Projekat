#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "pcb.h"
#include "syscall.h"

class KernelPCB : public PCB {
public:
	KernelPCB(StackSize stackSize, Time timeSlice);

	friend class Context;

private:
	static Syscall* syscallParams;

	static void syscallWrapper();
};

#endif
