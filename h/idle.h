#ifndef _IDLE_H_
#define _IDLE_H_

#include "pcb.h"

class IdlePCB : public PCB {
public:
	IdlePCB(StackSize stackSize, Time timeSlice);

private:
	static void idleWrapper();
};

extern IdlePCB* idlePCB;

#endif
