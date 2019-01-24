#include "thread.h"
#include "pcb.h"
#include "locks.h"

Thread::Thread(StackSize stackSize, Time timeSlice)
{
	LOCKED(
		myPCB = new PCB(stackSize, timeSlice, this);
	)
}

Thread::~Thread()
{
	LOCKED(
		waitToComplete();
		delete myPCB;
	)
}

void Thread::start()
{
	LOCKED(
		myPCB->reschedule();
	)
}

void Thread::waitToComplete()
{
	LOCKED(
		myPCB->waitToComplete();
	)
}

void Thread::sleep(Time timeToSleep)
{
	PCB::sleep(timeToSleep);
}

void dispatch()
{
	HARD_LOCKED(
		Context::requestChange();
		Context::timerInterrupt();
	)
}
