#ifndef _THREAD_H_
#define _THREAD_H_

#include "pcb.h"
#include "types.h"

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2; // default = 2*55ms

class Thread {
public:
	virtual ~Thread();

	void start();
	void waitToComplete();

	static void sleep(Time timeToSleep);

protected:
	friend class PCB;

	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);

	virtual void run() {}

private:
	PCB* myPCB;
};

void dispatch();

#endif
