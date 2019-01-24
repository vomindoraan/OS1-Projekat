#include "context.h"
#include "idle.h"
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
            mov tss, ss;
            mov tsp, sp;
            mov tbp, bp;
        }
        PCB::running->ss_ = tss;
        PCB::running->sp_ = tsp;
        PCB::running->bp_ = tbp;
        PCB::running->savedLock_ = lock;

        if (PCB::running->state() == PCB::RUNNING && PCB::running != Idle::instance()) {
            PCB::running->state(PCB::READY);
            Scheduler::put(PCB::running);
			HARD_LOCKED(cout << endl << requested_ << " put " << PCB::running << endl);
        }

        PCB::running = Scheduler::get();
		// HARD_LOCKED(cout << "get " << PCB::running << endl);
        if (!PCB::running) PCB::running = Idle::instance();
        PCB::running->state(PCB::RUNNING);
        PCB::running->timeLeft_ = PCB::running->timeSlice_;

        lock = PCB::running->savedLock_;
        tss = PCB::running->ss_;
        tsp = PCB::running->sp_;
        tbp = PCB::running->bp_;
        asm {
            mov ss, tss;
            mov sp, tsp;
            mov bp, tbp;
        }

        requested_ = false;
    }
}
