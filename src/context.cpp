#include "context.h"
#include "ivt.h"
#include "locks.h"
#include "system.h"

bool volatile Context::lockTimedOut_ = false;
bool volatile Context::requested_    = false;

static Register volatile tsp, tss, tbp;

void interrupt Context::timerInterrupt(...)
{
	Time& timeLeft = System::runningPCB->timeLeft_;

	if (!requested_) {
		oldTimerInterrupt();
		System::sleepList->wakeUp();
		tick();

		if (timeLeft > 0) {
			--timeLeft;
			if (timeLeft == 0 && lock) lockTimedOut_ = true;
		}
	}

	if (requested_ || (!System::runningPCB->unlimitedDuration() && timeLeft == 0 && !lock)) {
		asm {
			mov tss, ss;
			mov tsp, sp;
			mov tbp, bp;
		}
		System::runningPCB->ss_ = tss;
		System::runningPCB->sp_ = tsp;
		System::runningPCB->bp_ = tbp;
		System::runningPCB->savedLock_ = lock;

		if (System::runningPCB->state() == PCB::RUNNING
			&& System::runningPCB != System::idlePCB)
		{
			System::runningPCB->state(PCB::READY);
			Scheduler::put(System::runningPCB);
		}

		System::runningPCB = Scheduler::get();
		if (!System::runningPCB) System::runningPCB = System::idlePCB;
		System::runningPCB->state(PCB::RUNNING);
		System::runningPCB->timeLeft_ = System::runningPCB->timeSlice_;

		lock = System::runningPCB->savedLock_;
		tss = System::runningPCB->ss_;
		tsp = System::runningPCB->sp_;
		tbp = System::runningPCB->bp_;
		asm {
			mov ss, tss;
			mov sp, tsp;
			mov bp, tbp;
		}

		requested_ = false;
	}
}
