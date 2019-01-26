#include "context.h"
#include "idle.h"
#include "ivt.h"
#include "locks.h"
#include "pcb.h"
#include "sleeplst.h"

bool volatile Context::lockTimedOut_ = false;
bool volatile Context::requested_    = false;

static Register volatile tsp, tss, tbp;

void interrupt Context::timerInterrupt(...)
{
	Time& timeLeft = PCB::runningPCB->timeLeft_;

	if (!requested_) {
		oldTimerInterrupt();
		sleepList->wakeUp();
		tick();

		if (timeLeft > 0) {
			--timeLeft;
			if (timeLeft == 0 && lock) lockTimedOut_ = true;
		}
	}

	if (requested_ || (!PCB::runningPCB->unlimitedDuration() && timeLeft == 0 && !lock)) {
		asm {
			mov tss, ss;
			mov tsp, sp;
			mov tbp, bp;
		}
		PCB::runningPCB->ss_ = tss;
		PCB::runningPCB->sp_ = tsp;
		PCB::runningPCB->bp_ = tbp;
		PCB::runningPCB->savedLock_ = lock;

		if (PCB::runningPCB->state() == PCB::RUNNING && PCB::runningPCB != idlePCB) {
			PCB::runningPCB->state(PCB::READY);
			Scheduler::put(PCB::runningPCB);
		}

		PCB::runningPCB = Scheduler::get();
		if (!PCB::runningPCB) PCB::runningPCB = idlePCB;
		PCB::runningPCB->state(PCB::RUNNING);
		PCB::runningPCB->timeLeft_ = PCB::runningPCB->timeSlice_;

		lock = PCB::runningPCB->savedLock_;
		tss = PCB::runningPCB->ss_;
		tsp = PCB::runningPCB->sp_;
		tbp = PCB::runningPCB->bp_;
		asm {
			mov ss, tss;
			mov sp, tsp;
			mov bp, tbp;
		}

		requested_ = false;
	}
}
