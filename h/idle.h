#ifndef _IDLE_H_
#define _IDLE_H_

#include "pcb.h"

class Idle : public PCB {
public:
	static Idle* instance();

protected:
	Idle(StackSize stackSize, Time timeSlice);

private:
	static Idle* instance_;
	static void idleWrapper();
};

#endif
