#include "thread.h"
#include "locks.h"

Thread::Thread(StackSize stackSize, Time timeSlice)
    : myPCB(new PCB(this, stackSize, timeSlice))
{}

void dispatch()
{
    HARD_LOCKED(
        Context::requestChange();
        Context::timerInterrupt();
    )
}
