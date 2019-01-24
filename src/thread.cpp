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

void dispatch()
{
    HARD_LOCKED(
        Context::requestChange();
        Context::timerInterrupt();
    )
}
