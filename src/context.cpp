#include "context.h"
#include "ivt.h"
#include "locks.h"
#include "pcb.h"

bool volatile Context::lockTimedOut_ = false;
bool volatile Context::requested_ = false;

static Register volatile tsp, tss, tbp;

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
        asm {
            mov tsp, sp;
            mov tss, ss;
            mov tbp, bp;
        }
        PCB::running->saveRegs(tsp, tss, tbp);
        PCB::running->saveLock(lock);

        if (PCB::running->state() == PCB::RUNNING &&
            PCB::running->thread() != /* TODO */)
        {
            PCB::running->state(PCB::READY);
            Scheduler::put(PCB::running);
        }

        PCB::running = Scheduler::get();
        if (!PCB::running) PCB::running = /* TODO */;
        PCB::running->state(PCB::RUNNING);
        PCB::running->timeLeft_ = PCB::running->timeSlice();

        PCB::running->loadLock(lock);
        PCB::running->loadRegs(tsp, tss, tbp);
        asm {
            mov sp, tsp;
            mov ss, tss;
            mov bp, tbp;
        }

        requested_ = false;
    }
}
