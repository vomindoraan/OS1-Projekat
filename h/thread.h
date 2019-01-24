#ifndef _THREAD_H_
#define _THREAD_H_

#include "types.h"

StackSize const defaultStackSize = 4096;
Time const defaultTimeSlice = 2; // default = 2*55ms

class PCB; // Kernel's implementation of a user's thread

class Thread {
public:
	virtual ~Thread();

	void start();
	void waitToComplete();

	static void sleep(Time timeToSleep);

protected:
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);

	virtual void run() {}

	friend class PCB;

public:
	PCB* myPCB;
};

void dispatch();

#endif
