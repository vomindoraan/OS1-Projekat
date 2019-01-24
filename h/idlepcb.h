#ifndef _IDLEPCB_H_
#define _IDLEPCB_H_

#include "pcb.h"

class IdlePCB : public PCB {
public:
	IdlePCB(StackSize stackSize, Time timeSlice);

private:
	static void idleWrapper();
};

extern IdlePCB* idlePCB;

#endif
