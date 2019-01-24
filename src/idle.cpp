#include "idle.h"
#include <stdlib.h>

Idle* Idle::instance_ = NULL;

Idle* Idle::instance()
{
    if (!instance_) instance_ = new Idle(0x400UL, 1U);
    return instance_;
}

Idle::Idle(StackSize stackSize, Time timeSlice)
    : PCB(stackSize, timeSlice)
{
    initializeStack(Idle::idleWrapper);
}

void Idle::idleWrapper()
{
    while (true) {
        dispatch(); // TODO: Number of threads
    }
}