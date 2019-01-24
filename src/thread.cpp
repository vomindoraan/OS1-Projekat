#include "thread.h"
#include "pcb.h"
#include "locks.h"

Thread::Thread(StackSize stackSize, Time timeSlice)
{
    HARD_LOCKED(
        myPCB = new PCB(this, stackSize, timeSlice);
    )
}

void dispatch()
{
    HARD_LOCKED(
        Context::requestChange();
        Context::timerInterrupt();
    )
}
