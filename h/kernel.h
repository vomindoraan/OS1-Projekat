#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "pcb.h"

class KernelPCB : public PCB {
public:
	KernelPCB(StackSize stackSize, Time timeSlice);

private:
	static void syscallWrapper();
};

#endif
