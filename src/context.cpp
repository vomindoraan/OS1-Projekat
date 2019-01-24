#include "context.h"
#include "ivt.h"
#include "locks.h"
#include "pcb.h"

bool volatile Context::lockTimedOut_ = false;
bool volatile Context::requested_ = false;

void interrupt Context::timerInterrupt(...)
{
    Time& timeLeft = PCB::running->timeLeft_;

    if (!requested_) {
        oldTimerInterrupt();
        tick();

        if (timeLeft > 0) {
            --timeLeft;
            if (timeLeft == 0 && lock) lockTimedOut_ = true;
        }
    }

    if (requested_ || (!PCB::running->infinite() && timeLeft == 0 && !lock)) {

    }
}
